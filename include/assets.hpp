#pragma once

#include <boost/filesystem/path.hpp>
#include <string>
namespace jpeg2000{
namespace assets{
namespace paths{
    const std::string LENA_FILE =  boost::filesystem::path(__FILE__ ).parent_path().string() + "/../assets/lenaMiddleLine.txt";
}
}
}