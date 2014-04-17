/**
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 *
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 **/

#ifndef __APM_PRECLASS_DATA_H__
#define __APM_PRECLASS_DATA_H__

#ifndef APM_XGENE
#include <misc/xgene/cle/apm_cle_access.h>
#include <misc/xgene/cle/apm_cle_csr.h>
#else
#include "apm_cle_access.h"
#include "apm_cle_csr.h"
#endif

#define memcpy(dest,source,count)         CopyMem(dest,source,(UINTN)(count))
#define memcmp(buf1,buf2,count)           (int)(CompareMem(buf1,buf2,(UINTN)(count)))
#define memset(dest,ch,count)             SetMem(dest,(UINTN)(count),(UINT8)(ch))

/* CLE Port ids */
enum cle_port_ids {
	CLE_ENET_0 = 0,
	CLE_ENET_1,
	CLE_ENET_2,
	CLE_ENET_3,
	CLE_XGENET_0,
	CLE_XGENET_1,
	CLE_XGENET_2,
	CLE_XGENET_3,
	CLE_ENET_4,
	CLE_LA,
	MAX_CLE_PORTS,
};

/* CLE Parser idx */
enum cle_parser_idx {
	CLE_PARSER0 = 0,
	CLE_PARSER1,
	CLE_PARSER2,
	MAX_CLE_PARSERS,
};

/* Core ids */
enum cle_core_ids {
	CORE_0 = 0,
	CORE_1,
	MAX_SYSTEMS,
};

/* CLE Engine ids */
enum cle_engine_ids {
	CLE_0 = 0,	/* for CLE_ENET_0 & CLE_ENET_1 */
	CLE_1,		/* for CLE_ENET_2 & CLE_ENET_3 */
	XGCLE_0,	/* for CLE_XGENET_0 */
	XGCLE_1,	/* for CLE_XGENET_1 */
	XGCLE_2,	/* for CLE_XGENET_2 */
	XGCLE_3,	/* for CLE_XGENET_3 */
	CLE_LITE,	/* for CLE_ENET_4 */
	CLE_LAC,	/* for CLE_LA */
	MAX_CLE_ENGINE,
};

extern u32 PID2CID[MAX_CLE_PORTS];
extern u32 PORTPARSER[MAX_CLE_PORTS][2];
extern u32 CLEBASEPORTID[MAX_CLE_ENGINE];
extern u32 CLEPARSERS[MAX_CLE_ENGINE];

#define APM_CLE_ITER 100

#define IND_ADDR_PKT_RAM_0	0x00000000   /* Addr[31:29]-  000 */ 
#define IND_ADDR_PKT_RAM_1	0x20000000   /* Addr[31:29]-  001 */ 
#define IND_ADDR_PKT_RAM_2	0x40000000   /* Addr[31:29]-  010 */ 
#define IND_ADDR_PT_RAM		0xC0000000   /* Addr[31:28]-  1100 */ 
#define IND_ADDR_AVL_RAM	0xD0000000   /* Addr[31:28]-  1101 */
#define IND_ADDR_DB_RAM		0xE0000000   /* Addr[31:28]-  1110 */

/* Defines for compatibility with legacy Mamba SoC */
#ifndef CONFIG_APM862xx
#define READ_F2_RD CLE_READ_RD
#define READ_F2_WR CLE_READ_WR
#define WRITE_F2_RD CLE_WRITE_RD
#define WRITE_F2_WR CLE_WRITE_WR
#define WOL_MODE0_RD CLE_WOL_MODE0_RD
#define WOL_MODE0_WR CLE_WOL_MODE0_WR
#define WOL_MODE0_SET CLE_WOL_MODE0_SET
#endif

extern u8 apm_cle_system_id;
extern u8 apm_cle_systems;

extern u64 apm_class_base_addr_p[];
extern u64 apm_class_base_addr[];

/* Resource distribution as per MAX_SYSTEMS for AMP */
	/* node distribution 64 patricia tree node per core for AMP */
	/*  0 -  63 : Core 0 */
	/* 64 - 127 : Core 1 */

	/* result_ptr map approx 512 result pointers per core for AMP */
	/*   0        : Index 0 used commonly for dropping */
	/*   1 -  511 : Patricia Tree & AVL Tree Results for core 0 */
	/* 512 - 1023 : Patricia Tree & AVL Tree Results for core 1 */

/* Result/DB entry Related */
#ifdef CONFIG_APM862xx
#define MAX_DB_ENTRIES		1024
#define DB_ENTRY_SIZE		173
#else
#define MAX_DB_ENTRIES		512
#define DB_ENTRY_SIZE		179
#endif
#define START_DB_INDEX		0
#define END_DB_INDEX		(MAX_DB_ENTRIES - 1)

#define DEFAULT_DBPTR		(DFCLSRESDBPRIORITY0_WR(7) | START_DB_INDEX)
#define DBPTR_PER_SYSTEM	(MAX_DB_ENTRIES / apm_cle_systems)
#define SYSTEM_START_DBPTR	(apm_cle_system_id * DBPTR_PER_SYSTEM)
#define SYSTEM_END_DBPTR	(SYSTEM_START_DBPTR + DBPTR_PER_SYSTEM - 1)
#define DBPTR_OUT_RANGE(n,a)	(((n & ~DBPTR_AFLAG(a)) > END_DB_INDEX) || \
				(((DBPTR_INDEX(n) < SYSTEM_START_DBPTR) || \
				(DBPTR_INDEX(n) > SYSTEM_END_DBPTR)) && \
				(n & DBPTR_INDEX(0))))

/* Parser Node Related	*/
#define NODE_ENTRY_SIZE		512
#define MAX_NODE_ENTRIES	128	/**< Maximum number of physical
					   entries in patricia tree
					   database  */
#define REGS_PER_PTREE_NODE 	17  	/**< Maximum amount of data occupied
					   by a physical node entree in
					   32 bit reg file */
#define START_NODE_INDEX	0
#define END_NODE_INDEX		(MAX_NODE_ENTRIES - 1)
#define NODES_PER_SYSTEM	(MAX_NODE_ENTRIES / apm_cle_systems)
#define SYSTEM_START_NODE	(apm_cle_system_id * NODES_PER_SYSTEM)
#define SYSTEM_END_NODE		(SYSTEM_START_NODE + NODES_PER_SYSTEM - 1)
#define NODE_OUT_RANGE(n,a)	(((n & ~PTREE_AFLAG(a)) > END_NODE_INDEX) || \
				(((PTREE_INDEX(n) < SYSTEM_START_NODE) || \
				(PTREE_INDEX(n) > SYSTEM_END_NODE)) && \
				(n & PTREE_INDEX(0))))
#define PACKET_OUT_RANGE(p)	(p > 511)

#define LONG_PER_PTREE_NODE_STRUCT	(REGS_PER_PTREE_NODE + 2)
#define SIZE_PER_PTREE_NODE_STRUCT	(LONG_PER_PTREE_NODE_STRUCT * 4)

#ifdef CONFIG_APM862xx
#define EW_BRANCH(b)		((b & 0x7) << 1)
#define FW0_BRANCH(b)		((b & 0x3) << 1)
#define FW1_BRANCH(b)		(((b & 0x3) << 1) | 1)
#else
#define EW_BRANCH(b)		(b & 0x7)
#endif
#define KEY_INDEX(k)		(k & 0x1F)
#define JMP_ABS			0
#define JMP_REL			1
#define JMP_FW			0
#define JMP_BW			1
#define NO_BYTE			0
#define FIRST_BYTE		2
#define SECOND_BYTE		1
#define BOTH_BYTES		3
#define AVL_SEARCH(b)		(b)
#define STORE_KEY(b)		(b)

#define REGS_PER_DB    		6  	/* DB Entry is 172 Bits, Needs 6
					   words/registers */
#define MAX_LAST_NODES_TRACE  	16  	/**< Maximum amount of last visited
					   nodes trace supported */
#define MAX_FIRST_NODES_TRACE 	16  	/**< Maximum amount of first visited
					   node trace supported	*/
#define KEYNODE_COUNT	 	32  	/**< Maximum number of key nodes in
					   a single physical entry */
#define KEYNODE_INDEX	 	(KEYNODE_COUNT - 1)
					/**< Maximum number of key nodes index */

/* AVL Engine Node Related */
#define REGS_PER_AVL_SEARCH	8  	/**< Amount of 32 bit reg required for
					   AVL Node SEARCH */
#define REGS_PER_AVL_DEL	8  	/**< Amount of 32 bit reg required for
					   AVL Node DELETE */
#ifdef CONFIG_APM862xx
#define REGS_PER_AVL_ADD	9  	/**< Amount of 32 bit reg required for
					   AVL Node ADD */
#else
#define REGS_PER_AVL_ADD	10 	/**< Amount of 32 bit reg required for
					   AVL Node ADD */
#endif
#define REGS_PER_AVL_NODE 	10  	/**< Maximum amount of data occupied
					   by a physical node entree in
					   32 bit reg file */

/* AVL API return values */ 
#define APM_RC_OK	       	0
#define APM_RC_ERROR	       	-1
#define APM_RC_INVALID_PARM    	-2
#define APM_RC_FATAL	      	-3
#define APM_RC_CLE_MISS 	-4

/* AVL Search Int Errors */ 
#define APM_AVL_FATAL_WRSELF	 -10
#define APM_AVL_FATAL_RDSELF	 -11
#define APM_AVL_FATAL_WRBAL	 -12
#define APM_AVL_FATAL_RDBAL	 -13
#define APM_AVL_FATAL_MAXSTEP	 -14
#define APM_AVL_FATAL_RDRAM	 -15
#define APM_AVL_RDRAM		 -16
#define APM_AVL_DEL_NOSTR	 -17
#define APM_AVL_DEL_TREE_EMPTY	 -18
#define APM_AVL_ADD_DUP		 -19
#define APM_AVL_ADD_TREE_FULL	 -20

/** Preclassification operation types */
enum apm_preclass_hw_node_type_e 
{
	INVALID_NODE,			/*  000	 */ 
	KEY_NODE,			/*  001	 */ 
	EIGHT_WAY_NODE,			/*  010	 */ 
#ifdef CONFIG_APM862xx
	NODE_TYPE_RES_1,		/*  011	 */
	NODE_TYPE_RES_2,		/*  100	 */ 
	FOUR_WAY_NODE1_ONLY,		/*  101	 */ 
	FOUR_WAY_NODE2_ONLY,		/*  110	 */
	FOUR_WAY_NODE_BOTH		/*  111	 */ 
#else
	NODE_TYPE_RES,			/*  011	 */
#endif
};

#define START_NODE   	0 	/**< Start decision node */
#define INTERIM_NODE 	2 	/**< Intermediate decision node */
#define LAST_NODE    	1 	/**< Last decision node */

/** Preclassification hw global config */
struct apm_ptree_config
{
	u32 start_dbptr;       /**< start dbptr index allocation for the config */
	u32 start_node_ptr;    /**< start node ptr (bits [6:0] index into ram,
				bit [7] set if second node in a 4-way node) */
	u16 start_pkt_ptr;     /**< start packet ptr  */
	u32 default_result;    /**< default result    */
	u8 start_parser;       /**< start parser      */
	u8 max_hop;            /**< max hop number of node */
};

/** Preclassification operation types */
enum apm_preclass_op_type_e
{
	EQT,	/**< EQUAL TO = 0	   */
	NEQT,	/**< NOT EQUAL TO	   */
	LTEQT,	/**< LESS THAN EQUAL TO	   */
	GTEQT,	/**< GREATER THAN EQUAL TO */
	AND,	/**< Logical AND	   */
	NAND	/**< Logical NAND	   */
};

/** Node types */
enum apm_preclass_node_type_e
{
	INVALID_DN,	/**< Invalid decision node */
	EWDN = 1,	/**< 8 way decision node   */
#ifdef CONFIG_APM862xx
	FWDN,		/**< 4 way decision node   */
#endif
	KN		/**< Key node		   */
};

/** Per node branch data */
struct ptree_branch {
	u16 mask;	    /**< 16 bit	 mask */
	u16 data;	    /**< 16 bit comparison data */
	u32 operation;	    /**< see apm_preclass_op_type_e */
	u32 next_node_index; /**< 7 bit offset into the 128 patricia tree
				ram entries */
	u32 next_node_loc;  /**< node location in an entry, [0 or 1] for
				2 4-way decision
				nodes or [0 to 32] for 24 key nodes, ignored
				for 8-way decision node	 */
	u32 next_packet_pointer;
			 /**< Offset in packet from where to take 2 bytes to
			    compare (in 2 byte granularity) */
	u32 valid;	 /**< When not set, then the current decision is the
			      last comparison to be made at that node. When set
			       comparison to the next branch should be made */
	u32 jump_rel;	 /**< Jump Pointer is relattive to previous node */ 
	u32 jump_bw;	 /**< Jump Backward in Packet data from prv node */ 
};

struct ptree_kn {
	u32 priority;		/**< 3b: Result priority */
	u32 result_pointer;	/**< 10b: Result pointer  */
};

struct ptree_dn {
	u32 node_position;	/**< START_NODE, INTERIM_NODE, or LAST_NODE
				     1b: last node			*/
	u32 result_pointer;	/**< 10b: Default Result pointer	*/
	u32 search_byte_store;	/**< 2b: Enable search byte store to be
					 used for AVL search		*/
	u32 byte_store;		/**< 2b: Enable bye store		*/
	u32 header_length_store;	/**< 1b: Enable header length  store	*/
	u32 extension;		/**< 1b/2b: Enable chained comparison or Hdr Ext */
	u32 num;		/**< Number of Branches within node	*/
	const struct ptree_branch *branch;
};

/** Patricia tree node structure */
struct ptree_node {
	u32 index;    /**< Tree index, from 0-255			*/
	u32 type;      /**< see apm_preclass_node_type_e			*/
	u32 location;  /**< Location within an entry: 0 for EWDN,
				0/1 for FWDN, 0...31 for KN		*/
	const void *data;   /**< pointer to ptree_dn or ptree_kn	*/
};

/** Classifier Patricia Tree/Node/Branch Register Entry structures **/
#define SET_BRANCH_VALID	0x01
#define SET_BRANCH_MASK		0x02
#define SET_BRANCH_DATA		0x04
#define SET_BRANCH_OPERATION	0x08
#define SET_BRANCH_NNBR		0x10
#define SET_BRANCH_JUMP_REL	0x20
#define SET_BRANCH_JUMP_BW	0x40
#define SET_BRANCH_NPPTR	0x80

#define SET_BRANCH_MDO		(SET_BRANCH_MASK | \
				SET_BRANCH_DATA | \
				SET_BRANCH_OPERATION)

#define SET_BRANCH_ALL		(SET_BRANCH_VALID | \
				SET_BRANCH_MDO | \
				SET_BRANCH_NNBR | \
				SET_BRANCH_JUMP_REL | \
				SET_BRANCH_JUMP_BW | \
				SET_BRANCH_NPPTR)

struct apm_ptree_branch {
	unsigned valid     :  1;
	unsigned next_packet_pointer : 9;
	unsigned jump_bw   :  1;
	unsigned jump_rel  :  1;
	unsigned operation :  3;
	unsigned next_node_branch : 14;
	unsigned Rv3       : 3;
	unsigned data      : 16;
	unsigned mask      : 16;
} __attribute__ ((packed));

struct apm_ptree_ewdn {
	unsigned node_type : 2;
	unsigned last_node : 1;
	unsigned header_length_store : 1;
	unsigned extension : 2;
	unsigned byte_store : 2;
	unsigned search_byte_store : 2;
	unsigned Rv2 : 2;
	unsigned result_pointer : 12;
	unsigned Rv8 : 8;
	struct apm_ptree_branch branch[8];
} __attribute__ ((packed));

#ifdef CONFIG_APM862xx
struct apm_ptree_fwdn {
	unsigned result_pointer : 10;
	unsigned search_byte_store : 2;
	unsigned byte_store : 2;
	unsigned header_length_store : 1;
	unsigned last_node : 1;
	unsigned extension : 1;
	struct apm_ptree_branch branch[4];
} __attribute__ ((packed));
#endif

struct apm_ptree_key {
	unsigned priority : 3;
	unsigned result_pointer : 10;
	unsigned Rv3      : 3;
} __attribute__ ((packed));

struct apm_ptree_kn {
	unsigned node_type : 2;
	unsigned Rv30      : 30;
	struct apm_ptree_key key[32];
} __attribute__ ((packed));

struct apm_ptree_this {
	unsigned node_type : 2;
	unsigned Rv30      : 30;
	u32 Rv32[16];
} __attribute__ ((packed));

struct apm_ptree_node {
	union {
		struct apm_ptree_this this;
		struct apm_ptree_ewdn ewdn;
#ifdef CONFIG_APM862xx
		struct apm_ptree_fwdn fwdn[2];
#endif
		struct apm_ptree_kn kn;
	};
} __attribute__ ((packed));

/** Classifier Result/Database RAM Entry structure */
struct apm_cle_dbptr {
	unsigned split_boundary :  8;	    /* [7:0]  */ 
	unsigned mirror_nxtfpsel:  4;	    /* [11:8] */ 
	unsigned mirror_fpsel   :  4;	    /* [15:12] */ 
	unsigned mirror_dstqid  : 12;	    /* [27:16] */
	unsigned drop           :  1;	    /* [28] */
	unsigned mirror         :  1;	    /* [29] */
	unsigned hdr_data_split :  1;	    /* [30] */
	u64      h1_info_msb    : 48;	    /* [78:31] */
	unsigned h1_dr          :  1;	    /* [79] */ 
	unsigned h1_hr          :  1;	    /* [80] */
	u64      h0_info_msb    : 48;	    /* [128:81] */
	unsigned h0_enqnum      : 12;	    /* [140:129] */
	unsigned h0_fpsel       :  4;	    /* [144:141]  */
	unsigned nxtfpsel       :  4;	    /* [148:145]  */
	unsigned fpsel          :  4;	    /* [152:149]  */
	unsigned dstqid         : 12;	    /* [164:153]  */
	unsigned cle_priority   :  3;	    /* [167:165]  */
	unsigned cle_flowgroup  :  4;	    /* [171:168]  */
	unsigned cle_perflow    :  6;	    /* [177:172]  */
	unsigned cle_insert_timestamp: 1;   /* [178]  */
	unsigned stash          :  2;	    /* [180:179] */
	unsigned in             :  1;	    /* [181] */
	unsigned perprioen      :  1;	    /* [182]  */
	unsigned perflowgroupen :  1;	    /* [183]  */
	unsigned perflowen      :  1;	    /* [184]  */
	unsigned selhash        :  1;	    /* [185]  */
	unsigned selhdrext      :  1;	    /* [186]  */
	unsigned unused         :  5;	    /* [191:187]  */
	u32 index;
} __attribute__ ((packed));

/** Preclassification trace data structure */
struct apm_preclass_trace
{
	u8 last_node_visited;	/**< last node visited */
	u8 last_visited_node_trace[MAX_LAST_NODES_TRACE];
				/**< last 16 visited node trace */
	u8 first_visited_node_trace[MAX_FIRST_NODES_TRACE];
				/**< first 16 visited node trace */
};

/** Preclassification node entry config state structure */
struct apm_preclass_node_state
{
	u8 type;	 /**< see apm_preclass_node_type_e */
	u32 config_mask; /**< will use bits 0/0..1/0..23 */
};

/** Preclassification parser config state structure */
struct apm_preclass_state
{
	u32 start_parser[MAX_CLE_PARSERS];
	u32 ewdn_count;	/**< count of 8-way nodes configured */
#ifdef CONFIG_APM862xx
	u32 fwdn_count;	/**< count of 4-way nodes configured */
#endif
	u32 kn_count;	/**< count of key nodes configured   */
	struct apm_preclass_node_state node_state[MAX_NODE_ENTRIES];
			/**< used to save the node type encoding */
};

/* global data */
extern int apm_preclass_init_state[MAX_CLE_ENGINE];
extern struct apm_preclass_state sys_preclass_state[MAX_CLE_ENGINE];
int apm_preclassify_init(u32 cid);

#ifdef CLE_SHADOW
/**
 * @brief   Gets the start Patricia Node pointer of Shadow Patricia Nodes
 * @param   port - Inline-GE/LAC Port number
 * @return  Shadow Patricia Node Start Pointer
 */
struct apm_ptree_node *get_shadow_ptree_nodes(u32 port);

/**
 * @brief   Gets the start DB Result Pointer of Shadow dbptrs
 * @param   port - Inline-GE/LAC Port number
 * @return  Shadow DB Result Pointe
 */
struct apm_cle_dbptr *get_shadow_cle_dbptrs(u32 port);
#endif

/**
 * @brief   Pre-Classification parser global hardware config set routine for
 *	    a particular port.
 * @param   port - Inline-GE/LAC Port number
 * @param   struct apm_ptree_config * Global preclassification hw config
 *	    structure pointer
 * @return  APM_RC_OK or APM_RC_ERROR
 *
 */
int apm_set_sys_ptree_config(u8 port,
			struct apm_ptree_config *ptree_config);

/**
 * @brief   Pre-Classification parser global hardware get config routine for
 *	    a particular port.
 * @param   port - Inline-GE/LAC Port number
 * @param   struct apm_ptree_config * Global preclassification hw config
 *	    structure pointer
 * @return  APM_RC_OK or APM_RC_ERROR
 *
 */
int apm_get_sys_ptree_config(u8 port,
			struct apm_ptree_config *ptree_config);

/**
 * @brief   Patricia tree node-branch configuration routine.
 * @param   port - Inline-GE/LAC Port number
 * @param   node_index - Physical node index number (0-127).
 * @param   sub_node - Node 0 or 1 in a two 4-way node entry.
 * @param   branch_index - branch within a node or sub-node
 *	    (0-7 for 8-way, 0-3 for 4-way)
 * @param   branch_info - Patricia tree node-branch info
 * @param   set_branch_field - Set BitMask field SET_BRANCH_*
 * @return  APM_RC_OK or APM_RC_ERROR
 *
 */
int apm_set_ptree_node_branch(u8 port, u8 node_index,
				u8 sub_node, u8 branch_index,
				struct ptree_branch *pbranch,
				u32 set_branch_field);

/**
 * @brief   Clear node type field in a patricia tree ram entry for a particular
 *	    port.
 *	    Also clears software state (type) for a node entry enabling a new
 *	    configuration for the particular node entry.
 * @param   port - Inline-GE/LAC Port number (CLE_ENET_0/CLE_ENET_1).
 * @param   ptnode_index - Patricia Tree Node entry Index, 0 to 127.
 * @return  APM_RC_OK or APM_RC_ERROR
 *
 */
int apm_clear_ptree_node_type(u8 port, u8 ptnode_index);

/**
 * @brief   Get preclassification config state for a port.
 * @param   Inline-GE/LAC Port number
 * @param   preclass_state - pointer to configuration state structure
 * @return  APM_RC_OK or APM_RC_ERROR
 *
 */
int apm_get_preclass_state(u8 port, struct apm_preclass_state *preclass_state);

/**
 * @brief   Set preclassification tree node.
 * @param   port - Inline-GE/LAC Port number
 * @param   node_index - node index number.
 * @param   node - Pointer to set the APM Patricia Tree node
 * @return  APM_RC_OK or APM_RC_ERROR
 *
 */
int apm_set_ptree_node(u8 port, u8 node_index,
			struct apm_ptree_node *node);

/**
 * @brief   Get preclassification tree node.
 * @param   port - Inline-GE/LAC Port number
 * @param   node_index - node index number.
 * @param   node - Pointer to get the APM Patricia Tree node
 * @return  APM_RC_OK or APM_RC_ERROR
 *
 */
int apm_get_ptree_node(u8 port, u8 node_index,
			struct apm_ptree_node *node);

/**
 * @brief   Classification database entry config routine.
 * @param   port - Inline-GE/LAC Port number
 * @param   dbptr - Database entry structure
 * @return  APM_RC_OK or APM_RC_ERROR
 *
 */
int apm_set_cle_dbptr(u32 port, struct apm_cle_dbptr *dbptr);

/**
 * @brief   Classification database entry get config routine.
 * @param   port - Inline-GE/LAC Port number
 * @param   dbptr - Database entry structure
 * @return  APM_RC_OK or APM_RC_ERROR
 *
 */
int apm_get_cle_dbptr(u32 port, struct apm_cle_dbptr *dbptr);

/**
 * @brief   Get parser trace for a particular port.
 * @param   port - Inline-GE/LAC Port number
 * @param   preclass_trace - Pointer to structure containing trace info.
 * @return  APM_RC_OK or APM_RC_ERROR
 *
 */
int apm_get_preclass_trace(u8 port, struct apm_preclass_trace *preclass_trace);

/**
 * @brief   State/Stop Pre-Classification parser for a particular port.
 * @param   port - Inline-GE/LAC Port number
 * @param   state - Start 1 / Stop 0
 * @return  APM_RC_OK or APM_RC_ERROR
 *
 */
int apm_preclass_start_stop(u8 port, u32 state);

/**
 * @brief   Enables/Disables WoL mode operation in Pre Classifier. 
 * @param   enable - Enable/Disable WOL.  
 * @return  APM_RC_OK or APM_RC_ERROR
 */
int apm_preclass_wol_mode(int enable);

/**
 * @brief   Configures Parser node entry in Patricia RAM
 * @param   port - Inline-GE/LAC Port number
 * @param   node - Pointer to Node configurations
 * @return  APM_RC_OK or APM_RC_ERROR
 *
 */
int apm_ptree_node_config(u8 port, struct ptree_node *node);

/* Internal defines for decision node */
#define DN_TYPE_SIZE    0x3
#define DN_LN_SIZE      0x1
#define DN_HDRL_SIZE    0x1
#define DN_EXTENSION_SIZE   0x3
#define DN_BYTE_SIZE    0x3
#define DN_SEARCHB_SIZE 0X3
#define DN_DEFPTR_SIZE  0xFFF

#define DN_MASK_SIZE    0xFFFF
#define DN_NN_SIZE      0x1FF
#define DN_NB_SIZE      0x7
#define DN_NB_MASK      0xE00
#define DN_NB_SHIFT     9
#define DN_NNP_SIZE     (DN_NB_MASK | DN_NN_SIZE)
#define KN_NN_SIZE      0x1F
#define KN_NN_MASK      0x3E00
#define KN_NN_SHIFT     9
#define KN_NNP_SIZE     (KN_NN_MASK | DN_NN_SIZE)
#define DN_OP_SIZE      0x7
#define DN_JREL_SIZE    0x1
#define DN_JBW_SIZE     0x1
#define DN_NBP_SIZE     0x1FF
#define DN_VALID_SIZE   1
#define KN_PRI_SIZE     0x7
#define KN_PTR_SIZE     0x3FF

#ifndef bswap16
UINT16
bswap16(UINT16 x);
#endif

#ifndef bswap32
UINT32
bswap32(UINT32 x);
#endif

#ifndef ntohl
#define ntohl(x)  bswap32((uint32_t)(x))
#endif

#ifndef ntohs
#define ntohs(x)  bswap16((uint16_t)(x))
#endif

#ifndef htonl
#define htonl(x)  bswap32((uint32_t)(x))
#endif

#ifndef htons
#define htons(x)  bswap16((uint16_t)(x))
#endif

#endif	/* __APM_PRECLASS_DATA_H__  */
