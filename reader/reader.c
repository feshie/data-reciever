#include "pb_decode.h"
#include "pb_encode.h"
#include "pb_encode.c"
#include "pb_decode.c"
#include "readings.pb.h"
#include "readings.pb.c"
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int main(int argc, char *argv[])
{
  Sample sample;

  if(argc == 2)
  {
    FILE *pFile;
    pFile = fopen(argv[1], "r");

    uint8_t file_buf[1024];

    fread(file_buf, 1, 1024, pFile);

    pb_istream_t istream = pb_istream_from_buffer(file_buf, sizeof(file_buf)*sizeof(uint8_t));
    pb_decode_delimited(&istream, Sample_fields, &sample);

    /*##### TIME ##########################################################################*/
    printf("\tTime: %lu\n", sample.time);
    /*##### BATTERY #######################################################################*/
    printf("\tBatt: %f\n", sample.batt);
    /*##### TEMPERATURE ###################################################################*/
    printf("\tTemp: %f\n", sample.temp);
    /*##### ACCELEROMETER #################################################################*/
    if(sample.has_accX && sample.has_accY && sample.has_accZ)
    { // If all are present, then pitch/roll can be computed

      double X = (double)sample.accX;
      double Y = (double)sample.accY;
      double Z = (double)sample.accZ;

      double pitch = atan2(Y, Z) * 180/PI;
      double roll = atan2(X, sqrt(Y*Y + Z*Z)) * 180/PI;

      printf("\tPitch = %f\n", pitch);
      printf("\tRoll  = %f\n", roll);
    }

  }
  else
  {
    printf("Usage: %s FILENAME\n", argv[0]);
  }
}
