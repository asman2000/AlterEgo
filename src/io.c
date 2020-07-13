#include "io.h"

#include <proto/exec.h>
#include <proto/dos.h>

#include <dos/dosextens.h>

/*----------------------------------------------------------------------------*/

static const char* name = "sys";

void IoFlush(void)
{
	const struct StandardPacket* packet;
	const ULONG size = sizeof(struct StandardPacket);
	
	packet = (struct StandardPacket*)AllocMem(size, MEMF_CLEAR);

	if (NULL == packet)
	{
		return;
	}

	/*get filesystem message port*/
	struct MsgPort* const msg = DeviceProc(name);

	if (msg)
	{
		/*get our message port*/
		struct Process* process = (struct Process *)FindTask(NULL);
		struct MsgPort* processMsgPort = &(process->pr_MsgPort);

		/*fill in packet*/
		struct DosPacket* dospacket = &(packet->sp_Pkt);
		struct Message* message = &(packet->sp_Msg);

		/* hack Tripos packet to work with exec messaging system*/
		message->mn_Node.ln_Name = (char*)dospacket;
		message->mn_ReplyPort = processMsgPort;

		dospacket->dp_Link = message;
		dospacket->dp_Port = processMsgPort;
		dospacket->dp_Type = ACTION_FLUSH;

		/*send packet */
		PutMsg(msg, message);

		/*wait for reply*/
		WaitPort(processMsgPort);
		GetMsg(processMsgPort);
	}

	FreeMem(packet, size);
}

/*----------------------------------------------------------------------------*/
