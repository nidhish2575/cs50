#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_SIZE 512


int main(int argc, char *argv[])

{ //only accept 2 command line arguments
    if(argc!=2){

    printf("invalid input\n");
    return 1;
 }

 FILE *file = fopen(argv[1], "r");

// check if memory card opened successfully
 if(file==NULL)
 {
  printf("error ocurred\n");
  return 1;
 }

 // now we have valid file to read
 // open memory card
 typedef uint8_t BYTE;
 BYTE buffer[BLOCK_SIZE];

 size_t bytes_read;
 bool is_first_jpeg=false;
 FILE *current_file=NULL;
 char current_filename[100];
 int current_filenumber=0;
 bool found_jpeg=false;

 while(true)
 {
  //read 512 bytes into buffer and repeat until end

  bytes_read=fread(buffer,sizeof(BYTE),BLOCK_SIZE,file);

  if(bytes_read==0)
  {

   // indicates end of file
   break;
  }

  if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] && 0xf0==0xe0))
  {
   // if first jpeg then mark it
   found_jpeg=true;

   if(!is_first_jpeg)
   {

    is_first_jpeg=true;

   }
   else
   {
    // close the current file being written to and open new file
    fclose(current_file);
    }

    sprintf(current_filename,"%03i.jpg", current_filenumber);

    current_file=fopen(current_filename, "w");

    fwrite(buffer, sizeof(BYTE), bytes_read,current_file);

    current_filenumber++;





     //if already jpeg is found, keep writing to it
    if(found_jpeg)
    {

     fwrite(buffer, sizeof(BYTE), bytes_read,current_file);

    }



  }
}

fclose(file);
fclose(current_file);

return 0;
}