//http://keccak.noekeon.org/specs_summary.html

#include "hash.hpp"

#include <cstdint>
#include <cstring>

static const uint64_t round_constants[24]=
{
	0x0000000000000001,
	0x0000000000008082,
	0x800000000000808a,
	0x8000000080008000,
	0x000000000000808b,
	0x0000000080000001,
	0x8000000080008081,
	0x8000000000008009,
	0x000000000000008a,
	0x0000000000000088,
	0x0000000080008009,
	0x000000008000000a,
	0x000000008000808b,
	0x800000000000008b,
	0x8000000000008089,
	0x8000000000008003,
	0x8000000000008002,
	0x8000000000000080,
	0x000000000000800a,
	0x800000008000000a,
	0x8000000080008081,
	0x8000000000008080,
	0x0000000080000001,
	0x8000000080008008
};

static const uint64_t rotation_offsets[5][5]=
{
	{0,36,3,41,18},
	{1,44,10,45,2},
	{62,6,43,15,61},
	{28,55,25,21,56},
	{27,20,39,8,14}
};

static uint64_t rotl(const uint64_t xx,const size_t shift)
{
	return (xx<<(shift))|(xx>>(64-shift));
}

std::string hash_sha3_512(std::string message)
{
	size_t padding_length=72-((message.size())%72);

	for(size_t ii=0;ii<padding_length;++ii)
		message+=(char)0x00;

	if(padding_length>0)
	{
		message[message.size()-padding_length]|=0x01;
		message[message.size()-1]|=0x80;
	}

	uint64_t states[5][5];
	memset(states,0,8*5*5);

	for(size_t ii=0;ii<message.size()/72;++ii)
	{
		std::string block=message.substr(ii*72,72);

		for(size_t yy=0;yy<5;++yy)
			for(size_t xx=0;xx<5;++xx)
				if(xx+5*yy<9)
					states[xx][yy]^=*(uint64_t*)block.substr((xx+5*yy)*8,8).data();

		for(size_t round=0;round<24;++round)
		{
			uint64_t C[5];
			for(size_t ii=0;ii<5;++ii)
				C[ii]=states[ii][0]^states[ii][1]^states[ii][2]^states[ii][3]^states[ii][4];
			for(size_t ii=0;ii<5;++ii)
				for(size_t jj=0;jj<5;++jj)
					states[ii][jj]^=C[(ii+4)%5]^rotl(C[(ii+1)%5],1);

			uint64_t B[5][5];
			memset(B,0,8*5*5);
			for(size_t ii=0;ii<5;++ii)
				for(size_t jj=0;jj<5;++jj)
					B[jj][(2*ii+3*jj)%5]=rotl(states[ii][jj],rotation_offsets[ii][jj]);

			for(size_t ii=0;ii<5;++ii)
				for(size_t jj=0;jj<5;++jj)
					states[ii][jj]=B[ii][jj]^((~B[(ii+1)%5][jj])&B[(ii+2)%5][jj]);

			states[0][0]^=round_constants[round];
		}
	}

	std::string digest;

	for(size_t yy=0;yy<5;++yy)
		for(size_t xx=0;xx<5;++xx)
			if(xx+5*yy<9&&digest.size()<64)
				digest+=std::string((char*)&states[xx][yy],8);

	return digest;
}