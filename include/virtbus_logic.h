#ifndef __VIRTBUS_LOGIC
#define __VIRTBUS_LOGIC
#include <virtbus.h>
#include <message.h>
#include <dsm.h>
#include <nametree.h>
#define VIRTIO_BUS_PORT 418
#define MAX_EVENT_NR 256

#define MAX_CACHE_LINES 256
#define ENDPOINT_BUFFER_LENGTH (MAX_CACHE_LINES*(1<<CACHE_LINE_BIT)+4096)
/*this is the max buffer length with which we can recive data one time,
I suppose this would be OK*/

int start_virtbus_logic();
enum endpoint_state{
	endpoint_state_init=0,
	endpoint_state_tlv=1
};
struct endpoint{
	int fd_client;
	int is_pollout_scheduled;
	enum endpoint_state state;
	struct virtual_bus * bus_ptr;
	struct message_header msg_header;
	char bus_name[128];
	int32_t bus_quantum;
	
	char msg_buffer[ENDPOINT_BUFFER_LENGTH];
	
	char msg_send_buffer[ENDPOINT_BUFFER_LENGTH];
	int msg_send_buffer_iptr;
	int msg_send_buffer_pending;
	
	int msg_header_iptr;
	int msg_buffer_iptr;
	int msg_header_pending;
	int msg_buffer_pending;

	/*char msg_temp_buffer[ENDPOINT_BUFFER_LENGTH];*/
	uint32_t start_block_index;
	uint32_t nr_of_blocks;
	uint64_t target_version;
	void * data_ptr;
	int data_length;
	int is_gona_be_matched:1;
	int is_gona_lock_bus:1;
	
};
#endif