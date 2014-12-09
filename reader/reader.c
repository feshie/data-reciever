#include "pb_decode.h"
#include "pb_encode.h"
#include "readings.pb.h"
#include "rs485_message.pb.h"
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int main(int argc, char *argv[]){
    Sample sample;
    Rs485 rs485;
    FILE *pFile;
    pFile = fopen(argv[1], "r");
    uint8_t file_buf[1024];
    uint8_t i;
    uint8_t avr_bytes;
    uint8_t avr_data[Rs485_size];
    pb_istream_t main_istream;
    pb_istream_t avr_istream;

    double X, Y, Z;
    double pitch, roll;

    if(argc == 2){

        avr_bytes = 0;
        i = 0;
        fread(file_buf, 1, 1024, pFile);
        main_istream = pb_istream_from_buffer(file_buf, sizeof(file_buf));
        pb_decode_delimited(&main_istream, Sample_fields, &sample);
        /*##### TIME ##########################################################################*/
        printf("\tTime: %d\n", sample.time);
        /*##### BATTERY #######################################################################*/
        printf("\tBatt: %f\n", sample.batt);
        /*##### TEMPERATURE ###################################################################*/
        printf("\tTemp: %f\n", sample.temp);
        /*##### ACCELEROMETER #################################################################*/
        if(sample.has_accX && sample.has_accY && sample.has_accZ){ 
            // If all are present, then pitch/roll can be computed

              X = (double)sample.accX;
              Y = (double)sample.accY;
              Z = (double)sample.accZ;

              pitch = atan2(Y, Z) * 180/PI;
              roll = atan2(X, sqrt(Y*Y + Z*Z)) * 180/PI;
              printf("\tX = %d\n", sample.accX);
              printf("\tY = %d\n", sample.accY);
              printf("\tZ = %d\n", sample.accZ);
              printf("\tPitch = %f\n", pitch);
              printf("\tRoll  = %f\n", roll);
        }
        
        if(sample.has_ADC1){
            printf("\tADC1 = %d\n", (uint32_t)sample.ADC1);
        }

        if(sample.has_ADC2){
            printf("\tADC2 = %d\n", (uint32_t)sample.ADC2);
        }

        if(sample.has_rain){
            printf("\t Rain = %d\n", (uint32_t)sample.rain);
        }
        if(sample.has_AVR){
            avr_bytes = (uint8_t)sample.AVR.size;
            printf("\tHas %d bytes of AVR data\n", avr_bytes);
            printf("\t");
            for(i = 0; i < avr_bytes; i++){
                printf("%d,",sample.AVR.bytes[i]);
            }
            printf("\n");
            memcpy(avr_data, sample.AVR.bytes, avr_bytes);
            avr_istream = pb_istream_from_buffer(avr_data, avr_bytes);
            pb_decode(&avr_istream, Rs485_fields, &rs485);
            printf("\tType = %d\n", rs485.type);
            printf("\tSensor = %d\n", rs485.sensor); 
            printf("\tOW count = %d\n", (uint8_t)rs485.ow_count);
            printf("\tAD count = %d\n", (uint8_t)rs485.ad_count);
            printf("\tTAD count = %d\n", (uint8_t)rs485.tad_count);
            if(rs485.type == Rs485_Type_DATA){
                if(rs485.has_sensor){
                    if(rs485.sensor == Rs485_Sensor_OW){
                        printf("\tOne wire data\n");
                        printf("\t%d items of one wire data\n", (uint8_t)rs485.ow_count);
                        for(i=0; i< (uint8_t)rs485.ow_count; i++){
                            printf("\t%d:%f\n",rs485.ow[i].id, rs485.ow[i].value);
                        }
                    }else if(rs485.sensor == Rs485_Sensor_TA_CHAIN){
                        printf("\tChain data\n");
                        printf("TO IMPLEMENT\n");
                    }else if(rs485.sensor == Rs485_Sensor_WP){
                        printf("\tWater pressure\n");
                        printf("TO IMPLEMENT\n");
                    }else if(rs485.sensor == Rs485_Sensor_GAS){
                        printf("\tGas sensor\n");
                        printf("TO IMPLEMENT\n");
                    }else{
                        printf("ERR:Unknown sensor type!!\n");
                    }
                }else{
                    printf("ERR: No sensor type defined\n");
                }
            }else{
                printf("ERR:Not an AVR data protocol buffer\n");
            }
        } 

    }else{
        printf("Usage: %s FILENAME\n", argv[0]);
    }
}
