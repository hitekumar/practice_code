#include <stdio.h>
#include <stdlib.h>

//#define MAX_DATA_LENGTH     4294967295
#define MAX_DATA_LENGTH     1024*1024
struct record
{
    unsigned short type;
    unsigned int length;
    unsigned char data[MAX_DATA_LENGTH];
};

void read_record(char * record_file)
{
    FILE *fp = fopen(record_file, "r");
    struct record my_record;
    unsigned int buf;
    unsigned int long_read_count, short_read_count, byte_read_count;
    int i,j,k;
    if (fp != NULL)
    {
        do
        {
            if (fread(&my_record.type, sizeof(unsigned short), 1, fp))
            {
                my_record.type = ntohs(my_record.type);
            }
            if (fread(&my_record.length, sizeof(unsigned int), 1, fp))
            {
                my_record.length = ntohl(my_record.length);
            }
       
            if (my_record.length > MAX_DATA_LENGTH) 
            {
                printf("Error: Buffer is too small to read requested data length (%d)\n", 
				my_record.length);
                return;
            }
            long_read_count  = my_record.length/4;
            short_read_count = (my_record.length % 4)/2;
            byte_read_count = my_record.length % 2; 
            
            printf("Long read=%d Short read=%d Byte read=%d\n", 
			long_read_count, short_read_count, byte_read_count);
            for(i = 0; i < long_read_count; i++)
            {
                if (fread(&buf, sizeof(unsigned int), 1, fp))
                {
                    my_record.data[i*4] = ntohl(buf);
                }
                else
                {
                    printf("Error in read\n");
                    return;
                }
            }
        
            for(j = 0 ; j < short_read_count; j++)
            {
                if (fread(&buf, sizeof(unsigned short), 1, fp))
                {
                    my_record.data[i+(j*2)] = ntohs(buf);
                }   
                else
                {
                    printf("Error in read\n");
                    return;
                }
            }
        
            for(k = 0 ; k < byte_read_count; k++)
            {   
                if (fread(&buf, 1, 1, fp))
                {
                    my_record.data[i+j+k] = ntohs(buf);
                }                   
                else
                {
                    printf("Error in read\n");
                    return;
                }
            }
        
            printf("type %d\n", my_record.type);
            printf("Data as below of length %d\n", my_record.length);
            for (i = 0; i < my_record.length; i++ )
            {
                printf("0x%x ", my_record.data[i]);
                if ((i+1)%32 == 0)  printf("\n");
            }
        } while(my_record.length);
    }
}

int main()
{
    read_record("/tftpboot/appcpu");
}
