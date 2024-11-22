#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define N 330 /* height */
#define M 440 /* width */
#define filename "dog_440x330.yuv"
#define file_yuv "teleiothta3.yuv"
#define PI 3.14159265
#define iTile 22

/* code for armulator*/
#pragma arm section zidata="ram"
int current_y[N][M];
int current_u[N/2][M/2];
int current_v[N/2][M/2];
int table_A[N+2][M+2];
int newtable_A[N+2][M+2];
#pragma arm section

double angle =120;

int i,j, xx;
int new_y[N][M];
int new_u[N/2][M/2];
int new_v[N/2][M/2];

int x, y;
int hM = (M/2);
int hN = (N/2);
int hMuv = (M/4);
int hNuv = (N/4);
double sinma, cosma;
int xt, yt;
int xs,ys;

void read()
{
  FILE *frame_c;
  if((frame_c=fopen(filename,"rb"))==NULL)
  {
    printf("current frame doesn't exist\n");
    exit(-1);
  }

  for(i=0;i<N;i++)
  {
    for(j=0;j<M;j++)
    {
      current_y[i][j]=fgetc(frame_c);
    }
  }
    for(i=0;i<N/2;i++)
  {
    for(j=0;j<M/2;j++)
    {
      current_u[i][j]=fgetc(frame_c);
    }
  }
  for(i=0;i<N/2;i++)
  {
    for(j=0;j<M/2;j++)
    {
      current_v[i][j]=fgetc(frame_c);
    }
  }

  fclose(frame_c);
}

void write()
{
  FILE *frame_yuv;
  frame_yuv=fopen(file_yuv,"wb");

  for(i=0;i<N;i++)
  {
    for(j=0;j<M;j++)
    {
      fputc(new_y[i][j],frame_yuv);
    }
  }
    for(i=0;i<N/2;i++)
  {
    for(j=0;j<M/2;j++)
    {
      fputc(new_u[i][j],frame_yuv);
    }
  }

  for(i=0;i<N/2;i++)
  {
    for(j=0;j<M/2;j++)
    {
      fputc(new_v[i][j],frame_yuv);
    }
  }

  fclose(frame_yuv);
}

int main()
{
    read();
    
    sinma = sin(PI*angle/180);
    cosma = cos(PI*angle/180);

    for(x = 0; x < N+2; x++) {
    for(y = 0; y < M+2; y++) {
      table_A[x][y]=0;
      }
    }

    for(xx=1;xx,N+1;xx+=iTile) {
      for(y=1;y<M+1;y++){
        for(x=xx; x<xx+iTile; x++){
          table_A[x][y]=current_y[x-1][y-1];
          }
        }
      }
    

    for(xx=1;xx,N+1;xx+=iTile) {
      for(y=1;y<M+1;y++){
        for(x=xx; x<xx+iTile; x++){
          
            int xt = x - hM;
            int yt = y - hN;


             int xs = (int)((sinma * yt + cosma * xt) + hN);
            int ys = (int)((cosma * yt - sinma * xt) + hM);

            if(xs >= 0 && xs < N && ys >= 0 && ys < M) {
            newtable_A[x][y] = table_A[xs][ys];
            } else {
            newtable_A[x][y] = 0;
            }
        }
      }
    }
   

   for(xx=1; xx<N+1; xx+=iTile){
    for(y=1;y<M+1;j++){
      for(x=xx; x<xx+iTile; x++){
        current_y[i-1][j-1]=newtable_A[i][j];
      }
    }
   }
    
  for(xx=0; xx<N; xx+=iTile){
    for(y=0;y<M;y++){
      for(x=xx; x<xx+iTile; x++){
          current_y[x][y] += 127;
          if (current_y[x][y] > 255) current_y[x][y] = 255;
          if (current_y[x][y] < 0) current_y[x][y] = 0;
        }
    }

  }
    

  for(x = 0; x < N/2; x++) {
  for(y = 0; y < M/2; y++) {


    int xt = x - hMuv;
    int yt = y - hNuv;


    int xs = (int)((sinma * yt + cosma * xt) + hNuv);
    int ys = (int)((cosma * yt - sinma * xt) + hMuv);

    if(xs >= 0 && xs < N/2 && ys >= 0 && ys < M/2) {
      new_u[x][y] = current_u[xs][ys];

    } else {
      new_u[x][y] = 0;
    }
  }
  }

  for(x = 0; x < N/2; x++) {
  for(y = 0; y < M/2; y++) {


    int xt = x - hMuv;
    int yt = y - hNuv;


    int xs = (int)((sinma * yt + cosma * xt) + hNuv);
    int ys = (int)((cosma * yt - sinma * xt) + hMuv);

    if(xs >= 0 && xs < N/2 && ys >= 0 && ys < M/2) {
      new_v[x][y] = current_v[xs][ys];
    } else {
      new_v[x][y] = 0;
    }
  }
}

  write();
}


