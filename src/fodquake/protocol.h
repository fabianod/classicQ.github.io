/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#ifndef PROTOCOL_H
#define PROTOCOL_H

// protocol.h -- communications protocols

#include "qtypes.h"

#define	PROTOCOL_VERSION	28

#define QW_CHECK_HASH 0x5157

//=========================================

#define	PORT_CLIENT	27001
#define	PORT_MASTER	27000
#define	PORT_SERVER	27500

//=========================================

// out of band message id bytes

// M = master, S = server, C = client, A = any
// the second character will always be \n if the message isn't a single byte long (?? not true anymore?)

#define	S2C_CHALLENGE		'c'
#define	S2C_CONNECTION		'j'
#define	A2A_PING			'k'	// respond with an A2A_ACK
#define	A2A_ACK				'l'	// general acknowledgement without info
#define	A2A_NACK			'm'	// [+ comment] general failure
#define A2A_ECHO			'e' // for echoing
#define	A2C_PRINT			'n'	// print a message on client

#define	S2M_HEARTBEAT		'a'	// + serverinfo + userlist + fraglist
#define	A2C_CLIENT_COMMAND	'B'	// + command line
#define	S2M_SHUTDOWN		'C'


//==================
// note that there are some defs.qc that mirror to these numbers
// also related to svc_strings[] in cl_parse
//==================

// server to client
#define	svc_bad				0
#define	svc_nop				1
#define	svc_disconnect		2
#define	svc_updatestat		3	// [byte] [byte]
//define	svc_version			4	// [long] server version
#define	svc_setview			5	// [short] entity number
#define	svc_sound			6	// <see code>
#define	svc_time			7	// [float] server time
#define	svc_print			8	// [byte] id [string] null terminated string
#define	svc_stufftext		9	// [string] stuffed into client's console buffer
								// the string should be \n terminated
#define	svc_setangle		10	// [angle3] set the view angle to this absolute value
	
#define	svc_serverdata		11	// [long] protocol ...
#define	svc_lightstyle		12	// [byte] [string]
//define	svc_updatename		13	// [byte] [string]
#define	svc_updatefrags		14	// [byte] [short]
//define	svc_clientdata		15	// <shortbits + data>
#define	svc_stopsound		16	// <see code>
//define	svc_updatecolors	17	// [byte] [byte] [byte]
//define	svc_particle		18	// [vec3] <variable>
#define	svc_damage			19
	
#define	svc_spawnstatic		20
//	svc_spawnbinary		21
#define	svc_spawnbaseline	22
	
#define	svc_temp_entity		23	// variable
#define	svc_setpause		24	// [byte] on / off
//	svc_signonnum		25	// [byte]  used for the signon sequence

#define	svc_centerprint		26	// [string] to put in center of the screen

#define	svc_killedmonster	27
#define	svc_foundsecret		28

#define	svc_spawnstaticsound	29	// [coord3] [byte] samp [byte] vol [byte] aten

#define	svc_intermission	30		// [vec3_t] origin [vec3_t] angle
#define	svc_finale			31		// [string] text

#define	svc_cdtrack			32		// [byte] track
#define svc_sellscreen		33

#define	svc_smallkick		34		// set client punchangle to 2
#define	svc_bigkick			35		// set client punchangle to 4

#define	svc_updateping		36		// [byte] [short]
#define	svc_updateentertime	37		// [byte] [float]

#define	svc_updatestatlong	38		// [byte] [long]

#define	svc_muzzleflash		39		// [short] entity

#define	svc_updateuserinfo	40		// [byte] slot [long] uid
									// [string] userinfo

#define	svc_download		41		// [short] size [size bytes]
#define	svc_playerinfo		42		// variable
#define	svc_nails			43		// [byte] num [48 bits] xyzpy 12 12 12 4 8 
#define	svc_chokecount		44		// [byte] packets choked
#define	svc_modellist		45		// [strings]
#define	svc_soundlist		46		// [strings]
#define	svc_packetentities	47		// [...]
#define	svc_deltapacketentities	48		// [...]
#define svc_maxspeed		49		// maxspeed change, for prediction
#define svc_entgravity		50		// gravity change, for prediction
#define svc_setinfo			51		// setinfo on a client
#define svc_serverinfo		52		// serverinfo
#define svc_updatepl		53		// [byte] [byte]
#define svc_nails2			54		

/******************
 * FTE extensions *
 ******************/

#define svcfte_lightstylecol    57 /* FTEX_LIGHTSTYLECOLOUR */
#define svcfte_spawnbaseline2   66 /* FTEX_SPAWNSTATIC2 || FTEX_REPLACEMENTDELTAS */
#define svcfte_updatestatfloat  79 /* FTEX_CSQC */

/********************
 * Qizmo extensions *
 ********************/

#define svc_qizmovoice		83
//==============================================

// client to server
#define	clc_bad			0
#define	clc_nop 		1
//define	clc_doublemove	2
#define	clc_move		3		// [[usercmd_t]
#define	clc_stringcmd	4		// [string] message
#define	clc_delta		5		// [byte] sequence number, requests delta compression of message
#define clc_tmove		6		// teleport request, spectator only
#define clc_upload		7		// teleport request, spectator only

//==============================================

// playerinfo flags from server
// playerinfo always sends: playernum, flags, origin[] and framenumber

#define	PF_MSEC         (1 << 0)
#define	PF_COMMAND      (1 << 1)
#define	PF_VELOCITY1    (1 << 2)
#define	PF_VELOCITY2    (1 << 3)
#define	PF_VELOCITY3    (1 << 4)
#define	PF_MODEL        (1 << 5)
#define	PF_SKINNUM      (1 << 6)
#define	PF_EFFECTS      (1 << 7)
#define	PF_WEAPONFRAME  (1 << 8)		// only sent for view player
#define	PF_DEAD         (1 << 9)		// don't block movement any more
#define	PF_GIB          (1 << 10)		// offset the view height differently
// bits 11..13 are player move type bits
#define PF_PMC_SHIFT    11
#define	PF_PMC_MASK     7

// player move types
#define PMC_NORMAL              0		// normal ground movement
#define PMC_NORMAL_JUMP_HELD    1		// a fake move type for jump debouncing
#define PMC_OLD_SPECTATOR       2		// fly through walls (QW compatibility mode)
#define PMC_SPECTATOR           3		// fly through walls
#define PMC_FLY                 4		// fly, bump into walls

//==============================================

// if the high bit of the client to server byte is set, the low bits are
// client move cmd bits
// ms and angle2 are always sent, the others are optional
#define	CM_ANGLE1       (1 << 0)
#define	CM_ANGLE3       (1 << 1)
#define	CM_FORWARD      (1 << 2)
#define	CM_SIDE         (1 << 3)
#define	CM_UP           (1 << 4)
#define	CM_BUTTONS      (1 << 5)
#define	CM_IMPULSE      (1 << 6)
#define	CM_ANGLE2       (1 << 7)

//==============================================


#define DF_ORIGIN         1
#define DF_ANGLES         (1 << 3)
#define DF_EFFECTS        (1 << 6)
#define DF_SKINNUM        (1 << 7)
#define DF_DEAD           (1 << 8)
#define DF_GIB            (1 << 9)
#define DF_WEAPONFRAME    (1 << 10)
#define DF_MODEL          (1 << 11)


//==============================================

// the first 16 bits of a packetentities update holds 9 bits of entity number and 7 bits of flags
#define	U_ORIGIN1       (1 << 9)
#define	U_ORIGIN2       (1 << 10)
#define	U_ORIGIN3       (1 << 11)
#define	U_ANGLE2        (1 << 12)
#define	U_FRAME         (1 << 13)
#define	U_REMOVE        (1 << 14)		// REMOVE this entity, don't add it
#define	U_MOREBITS      (1 << 15)

// if MOREBITS is set, these additional flags are read in next
#define	U_ANGLE1        (1 << 0)
#define	U_ANGLE3        (1 << 1)
#define	U_MODEL	        (1 << 2)
#define	U_COLORMAP      (1 << 3)
#define	U_SKIN	        (1 << 4)
#define	U_EFFECTS       (1 << 5)
#define	U_SOLID         (1 << 6)		// the entity should be solid for prediction

/******************
 * FTE extensions *
 ******************/

#define FTE_U_EVENMORE      (1 << 7)		/* Used by FTEX_SCALE, FTEX_TRANS, FTEX_FATNESS, FTEX_MODELDOUBLE, FTEX_HEXEN2, FTEX_COLOURMOD, FTEX_DPFLAGS, FTEX_ENTITYDBL, FTEX_ENTITYDBL2 and probably a lot more... */

#define FTE_U2_SCALE        (1 << 0)
#define FTE_U2_TRANS        (1 << 1)
#define FTE_U2_FATNESS      (1 << 2)
#define FTE_U2_MODELDBL     (1 << 3)
#define FTE_U2_UNUSED1      (1 << 4)
#define FTE_U2_ENTITYDBL    (1 << 5)
#define FTE_U2_ENTITYDBL2   (1 << 6)
#define FTE_U2_YETMORE      (1 << 7)
#define FTE_U2_DRAWFLAGS    (1 << 8)
#define FTE_U2_ABSLIGHT     (1 << 9)
#define FTE_U2_COLOURMOD    (1 << 10)
#define FTE_U2_DPFLAGS      (1 << 11)
#define FTE_U2_TAGINFO      (1 << 12)
#define FTE_U2_LIGHT        (1 << 13)
#define FTE_U2_EFFECT16     (1 << 14)
#define FTE_U2_FARMORE      (1 << 15)

//==============================================

// a sound with no channel is a local only sound
// the sound field has bits 0-2: channel, 3-12: entity
#define	SND_VOLUME         (1 << 15)		// a byte
#define	SND_ATTENUATION    (1 << 14)		// a byte

#define DEFAULT_SOUND_PACKET_VOLUME 255
#define DEFAULT_SOUND_PACKET_ATTENUATION 1.0

// svc_print messages have an id, so messages can be filtered
#define	PRINT_LOW               0
#define	PRINT_MEDIUM            1
#define	PRINT_HIGH              2
#define	PRINT_CHAT              3	// also go to chat buffer

// temp entity events
#define	TE_SPIKE                0
#define	TE_SUPERSPIKE           1
#define	TE_GUNSHOT              2
#define	TE_EXPLOSION            3
#define	TE_TAREXPLOSION         4
#define	TE_LIGHTNING1           5
#define	TE_LIGHTNING2           6
#define	TE_WIZSPIKE             7
#define	TE_KNIGHTSPIKE          8
#define	TE_LIGHTNING3           9
#define	TE_LAVASPLASH           10
#define	TE_TELEPORT             11
#define	TE_BLOOD                12
#define	TE_LIGHTNINGBLOOD       13

//==============================================

// ZQuake protocol extensions (*z_ext serverinfo key)
#define Z_EXT_PM_TYPE           (1 << 0)
#define Z_EXT_PM_TYPE_NEW       (1 << 1)
#define Z_EXT_SERVERTIME        (1 << 3)

#define Z_EXT_JOIN_OBSERVE      (1 << 5)

#define SUPPORTED_EXTENSIONS    (Z_EXT_PM_TYPE|Z_EXT_PM_TYPE_NEW|Z_EXT_SERVERTIME|Z_EXT_JOIN_OBSERVE)

#define QW_PROTOEXT_HUFF 0x46465548
#define QW_PROTOEXT_FTEX 0x58455446
#define QW_PROTOEXT_FTE2 0x32455446

#define FTEX_SCALE            0x00000002
#define FTEX_LIGHTSTYLECOLOUR 0x00000004
#define FTEX_TRANS            0x00000008
#define FTEX_FATNESS          0x00000100
#define FTEX_MODELDOUBLE      0x00001000
#define FTEX_COLOURMOD        0x00080000
#define FTEX_SPAWNBASELINE2   0x00400000
#define FTEX_CHUNKEDDOWNLOADS 0x20000000
#define FTEX_CSQC             0x40000000

#define FTEX_SUPPORTED (FTEX_CHUNKEDDOWNLOADS)

/*
==========================================================
  ELEMENTS COMMUNICATED ACROSS THE NET
==========================================================
*/

#define	MAX_CLIENTS       32

#define	UPDATE_BACKUP     64	// copies of entity_state_t to keep buffered (must be power of two)
#define	UPDATE_MASK       (UPDATE_BACKUP - 1)

// entity_state_t is the information conveyed from the server
// in an update message
typedef struct entity_state_s
{
	int number;			// edict index
	int flags;			// nolerp, etc
	vec3_t origin;
	vec3_t angles;
	int modelindex;
	int frame;
	int colormap;
	int skinnum;
	int effects;
} entity_state_t;

#ifdef SERVERONLY

#define	MAX_PACKET_ENTITIES	64

typedef struct packet_entities_s
{
	int num_entities;
	entity_state_t entities[MAX_PACKET_ENTITIES];
} packet_entities_t;

#else

#define	MAX_MVD_PACKET_ENTITIES	300		
#define	MAX_PACKET_ENTITIES	64

typedef struct packet_entities_s
{
	int num_entities;
	entity_state_t entities[MAX_MVD_PACKET_ENTITIES];
} packet_entities_t;

#endif

typedef struct usercmd_s
{
	byte msec;
	vec3_t angles;
	short forwardmove, sidemove, upmove;
	byte buttons;
	byte impulse;
} usercmd_t;

// usercmd button bits
#define BUTTON_ATTACK     (1 << 0)
#define BUTTON_JUMP       (1 << 1)
#define BUTTON_USE        (1 << 2)


#define dem_cmd         0
#define dem_read        1
#define dem_set         2
#define dem_multiple    3
#define	dem_single      4
#define dem_stats       5
#define dem_all         6

#endif
