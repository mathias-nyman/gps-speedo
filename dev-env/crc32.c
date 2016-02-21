/*******************************************************************************
  crc32.c by elektron

  Compile: 

    # gcc -lz -o crc32 crc32.c

  Usage:   
    # ./crc32 -h

    crc32 by elektron
      crc32 [-h] file1 [fileN...]


  Notes:   
    This is a hack from someone elses code :
     http://www.linuxquestions.org/questi...hreadid=199640   

    Find the most current version of this application at:
         http://kremlor.net/projects/crc32


*******************************************************************************/



#include <errno.h>
#include <stdio.h>
#include <zlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>

int usage( char *progname )
{ 
  printf( "%s by elektron\n", progname);
  printf( "  %s [-h] file1 [fileN...]\n\n", progname );
}

unsigned long getFileSize( char *filename )
{
  FILE *input_file;
  unsigned long file_size;

  input_file = fopen( filename, "r" );
  if( input_file == NULL )
  { 
    printf( "Could not open %s for reading.\n", filename );
    return 0;
  }

  fseek( input_file, 0, SEEK_END );
  file_size = ftell( input_file );
  rewind( input_file);

  fclose( input_file );
  return file_size;

}

unsigned long computeCRC32( char *filename )
{ 
  int input_fd;
  char *file_buffer;
  unsigned long file_size;
  unsigned long chunk_size=1024;
  unsigned long bytes_read;
  unsigned long crc=0L;

  file_size = getFileSize( filename );

  if( file_size == 0 )
  { 
    printf( "File size is calculated to be 0. Cannot calculate CRC\n" );
    return 0;
  }

  file_buffer = (char *)malloc( chunk_size );
  if( file_buffer == NULL )
  { 
    printf( "Unable to reserve enough memory for file buffer.\n" );
    return 0;
  }
  crc = crc32( 0L, Z_NULL, 0 );

  input_fd = open( filename, O_RDONLY );
  if( input_fd == -1 )
  { 
    printf( "Could not open %s for reading.\n", filename );
    return 0;
  }
  while( 1 ){

   bytes_read = read( input_fd, file_buffer, chunk_size );

   if (bytes_read == 0 ) {
        break;
   }
   if (bytes_read == -1 ) {
        perror("read");
        break;
   }

   crc = crc32( crc, file_buffer, bytes_read );

  }

  free( file_buffer );

  close( input_fd );

  return crc;
}

int main( int argc, char *argv[] )
{ 
  unsigned long crc=0L;
  extern char *optarg;
  extern int optind, opterr, optopt;
  int i;

  while ( getopt( argc, argv, "h" ) != -1 ) {
  //    printf("optarg = %s, optind = %d, opterr = %d, optopt = %d\n",
  //            optarg, optind, opterr, optopt);
        if ( strncmp( argv[optind-1], "-h", 2 ) == 0 ) {
                usage( basename(argv[0]) );
                return 0;
        }
  }
 //printf("optarg = %s, optind = %d, opterr = %d, optopt = %d, argc = %d\n",
 //     optarg, optind, opterr, optopt, argc);


  if( argc < optind+1 )
  { 
    printf( "I need at least one filename to calculate crc on\n" );
    return 1;
  }
  for ( i=optind; i<argc; i++){
    crc = computeCRC32(argv[i] );

    printf("%08x\n",crc );
  }
}
