#ifndef HASH_HPP
#define HASH_HPP

#include <string>

std::string hash_sha3_512(std::string message);

std::string hmac_sha3_512(std::string key,const std::string& plain);

#endif