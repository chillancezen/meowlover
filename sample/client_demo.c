#include <virtbus_client.h>
#include <virt_cache.h>
#include <virt_cpu.h>
int main()
{
	#if 0
	int fd=socket(AF_INET,SOCK_STREAM,0);
	char buffer[1024];
	
	assert(fd);
	struct sockaddr_in server_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(418);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	int rc=connect(fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_in));
	assert(!rc);
	
	struct message_builder mb;
	rc=message_builder_init(&mb,buffer,sizeof(buffer));
	assert(!rc);
	struct tlv_header tlv;
	tlv.type=MESSAGE_TLV_TYPE_JOIN_BUS;
	tlv.length=4;
	rc=message_builder_add_tlv(&mb,&tlv,"hello world");
	tlv.type=MESSAGE_TLV_TYPE_END;
	tlv.length=0;
	rc=message_builder_add_tlv(&mb,&tlv,"hello world");
	assert(!rc);
	printf("%d\n",mb.message_header_ptr->total_length);

	rc=send(fd,mb.buffer,mb.message_header_ptr->total_length,0);
	assert(rc==(mb.message_header_ptr->total_length));
	memset(buffer,0x0,sizeof(buffer));
	rc=recv(fd,buffer,sizeof(buffer),0);
	printf("%d:%s\n",rc,buffer);
	getchar();
	#endif
	#if 0
	uint64_t version=0;
	int is_modified;
	int is_matched;
	char buffer[2048];
	
	struct client_endpoint * cep=client_endpoint_alloc_and_init("172.16.1.200");
	int rc=client_endpoint_connect_to_virtual_bus(cep,"/root/cute",64);
	printf("real number of blocks :%d\n",cep->nr_of_blocks);
	//rc=client_endpoint_write_virtual_bus_matched(cep,1,1,"hello 1st section~",&is_matched,&version);
	rc=client_endpoint_write_virtual_bus_generic(cep,0,1,"hello 1st section~",&version);
	rc=client_endpoint_write_virtual_bus_generic(cep,1,1,"hello 2st section~",&version);
	printf("write matched:%d %d %ld\n",rc,is_matched,version);
	version=2;
	rc=client_endpoint_read_virtual_bus_matched(cep,0,2,buffer,&version,&is_modified);
	//rc=client_endpoint_read_virtual_bus_raw(cep,1,2,buffer);
	printf("read matched:%d %d %ld %s\n",rc,is_modified,version,buffer+64);
	
	printf("connect:%d\n",rc);
	rc=client_endpoint_write_virtual_bus_generic(cep,0,1,"hello world",&version);
	printf("write:%d  %ld\n",rc,version);

	version=0;
	rc=client_endpoint_read_virtual_bus_matched(cep,0,1,buffer,&version,&is_modified);
	//rc=client_endpoint_read_virtual_bus_raw(cep,0,2,buffer);
	printf("read:%d %d %ld %s\n",rc,is_modified,version,buffer);
	
	getchar();
	
	struct local_memory * mem=local_memoory_alloc("172.16.1.200","/root/cute",64);
	#endif
	struct virt_cpu *cpu=create_virt_cpu();
	cpu->cache=local_memoory_alloc("172.16.1.52","/root/cute",64);

	#if 1
	strcpy(cpu->cache->local_memory_base,"hello DSM");
	//STORE(cpu,cpu->cache->local_memory_base,64);
	LOAD(cpu,cpu->cache->local_memory_base,64);

	CMPXCHG(cpu,cpu->cache->local_memory_base,64);
	printf("REG4:%d\n",cpu->reg4);
	printf("REG5:%d\n",cpu->reg5);
	#else
	LOAD(cpu,cpu->cache->local_memory_base,64);
	LOAD(cpu,cpu->cache->local_memory_base,64);
	printf("content:%s\n",cpu->cache->local_memory_base);
	#endif
	getchar();
	
	return 0;
	
}
