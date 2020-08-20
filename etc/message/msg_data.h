#ifndef __MSG_DATA_H__
#define __MSF_DATA_H__

struct real_data
{
	int numOfFace;
};

struct message
{
	long msg_type;
	struct real_data data;
};

#endif
