#include "quantlm.hpp"


namespace jpeg2000{

    // Quantizes the signal x of size n with nq quantized values
    // Returns the quantized signal of x
    // See quantlm_idx to get the indexed quantifier for each values of x

    // if idx:
    // Get the indexed quantifier for each values of x
    // Quantizes the signal x of size n with nq quantized values
    // Returns the indexed quantifier of each value of x
    // See quantlm to get the quantized signal

    void quantlm(double* x,int n,int nq, bool isIdx) {
        // q is the centroid
        // qi a i that x[i] is associated to qi
        // qn is the number of x associated to qi
        double* q=(double *)calloc(nq,sizeof(double));
        int* qi=(int *)calloc(n,sizeof(int));
        int* qn=(int *)calloc(nq,sizeof(int));
        double dmean=0.0;


        // Uniform initialization of the centroids
        double xmin=x[0];
        double xmax=x[0];
        for (int i=0;i<n;i++) {
            if (xmin>x[i]) xmin=x[i];
            if (xmax<x[i]) xmax=x[i];
        }

        for (int i=0;i<nq;i++) {
            q[i]=xmin+(xmax-xmin)*(i+1.0)/(nq+1.0);
        }

        //printf("init\n");

        for (int i=0;i<100;i++) {
            //printf ("step %d dmean=%f\n",i,dmean);

            // Clustering - every points is associated with its nearest neighbour
            for (int i = 0; i < nq; i++) qn[i] = 0;

            dmean = 0.0;

            for (int i = 0; i < n; i++) {
                double distmin = 1.0e30;
                int qdistmin = 0;
                for (int j = 0; j < nq; j++) {
                    double d1 = (x[i] - q[j]);
                    double dist = d1 * d1;
                    if (dist < distmin) {
                        distmin = dist;
                        qdistmin = j;
                    }
                }
                qn[qdistmin]++;
                //printf("i=%d x[i]=%f qi[i]=%d\n",i,x[i],qdistmin);
                qi[i] = qdistmin;
                dmean += distmin;
            }

            dmean /= n;

            // Moving centroids in the barycentre of their class
            for (int i = 0; i < nq; i++) {
                // Empty class
                if (qn[i] != 0) q[i] = 0.0;
            }
            if (nq > 0) {

                for (int i = 0; i < n; i++) {
                    int qq = qi[i];
                    q[qq] += x[i];
                }
            }
            for (int i=0;i<nq;i++) {
                if (qn[i]!=0) q[i]/=qn[i];
            }

            // Process one empty class
            // Put the centroid of such class near the biggest class
            bool running=true;
            for (int i=0;i<nq && running;i++) {
                if (qn[i]==0) {
                    int bigq=0;

                    for (int j=0;j<nq;j++) {
                        if (qn[j]>qn[bigq]) bigq=j;
                    }

                    q[i]=q[bigq]+0.00001;
                    running=false;
                }
            }
        }

        //for (int i=0;i<nq;i++) {
        //  printf("q[%d]=%f nq=%d\n",i,q[i],qn[i]);
        //}

        for (int i=0;i<n;i++) {
            //printf("x[%d]=%f qx[%d]=%f\n",i,x[i],i,qi[i]);
            if(isIdx)
                x[i]=qi[i];
            else
                x[i]=q[qi[i]];
        }

        free(q);
        free(qi);
        free(qn);
    }
}
