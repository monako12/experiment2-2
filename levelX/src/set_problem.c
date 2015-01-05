#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parameter.h"


extern double i_lay[CTG][INPUT+1];
extern double teach[CTG][OUTPUT];
extern void print_teach(int index);
extern double test_pattern[INPUT+1];
extern double correct[OUTPUT];

extern void print_correct();

void set_problem();
void nn_read_test_pattern();


void set_problem(){
  FILE *read_file;
  FILE *read_file2; /* file I/O for each problem */
  char *filename;
  //char *filename2;  /* name for each problem */
  int count;
  int count_x, count_y;       /* for line number on each problem */
  char buff[FGETS_LEN];
  char c[2];
  int buff_i;
  int i;

  /* initialize */
  filename = (char *)malloc(sizeof(char)*FGETS_LEN);
  if( filename == NULL ){
    fprintf(stdout,"# ERROR! malloc(filename) was failed in set_problem()\n");
    fprintf(stderr,"# ERROR! malloc(filename) was failed in set_problem()\n");
    exit(-1);
  }
  //printf("sizeof(buff)=%d, (filename)=%d\n",(int)sizeof(buff),(int)sizeof(filename));

  /* read filename -> set test cases */
  read_file = fopen(PROBLEM,"r");
  if( read_file == NULL ){
    fprintf(stdout,"# ERROR! fopen(%s) was failed in set_problem()\n",PROBLEM);
    fprintf(stderr,"# ERROR! fopen(%s) was failed in set_problem()\n",PROBLEM);
    exit(-1);
  }
  for(count=0; count<CTG; count++){
    fflush(stdout);
    fgets(buff, sizeof(buff), read_file);
    sscanf(buff,"%s",filename);
    //printf("count=%d, filename=%s\n",count,filename);

    read_file2 = fopen(filename,"r");
    if( read_file2 == NULL ){
      // fprintf(stdout,"# ERROR! fopen(%s) was failed in set_problem(). count=%d\n",filename,count);
      // fprintf(stderr,"# ERROR! fopen(%s) was failed in set_problem(). count=%d\n",filename,count);
      exit(-1);
    }

    /* read a part of ANSWER */
    fflush(stdout);
    fgets(buff, sizeof(buff), read_file2);
    //printf("test3: buff=%s, count=%d\n",buff,count);
    //printf("-> atoi(buff)=%d, atof(buff)=%lf\n",atoi(buff),atof(buff));
    buff_i = atoi(buff);
    for(i=0; i<OUTPUT; i++){
      if( i==buff_i ){
	teach[count][i] = ON;
      }else{
	teach[count][i] = OFF;
      }
    }
    //sscanf(buff,"%d",teach[count][0]);
    print_teach(count);

    for(count_y=0; count_y<SIZE_Y; count_y++){
      fflush(stdout);
      fgets(buff, sizeof(buff), read_file2);
      //printf("test4: buff=%s\n",buff);
      for(count_x=0; count_x<SIZE_X; count_x++){
	c[0] = *(buff + count_x);
	c[1] = '\0';
        if( atoi(c) == 1 ){
            i_lay[count][(count_y*SIZE_X)+count_x] = ON;
	    // fprintf(stdout,"1");
        }else if( atoi(c) == 0 ){
            i_lay[count][(count_y*SIZE_X)+count_x] = OFF;
	    // fprintf(stdout,"0");
        }else{
	  //    fprintf(stderr,"#ERROR! atoi() reading from %s was failed.",PROBLEM);
            exit(1);
        }
      }
      i_lay[count][(count_y*SIZE_X)+count_x] = ON; /* bias */
      //      fprintf(stdout,"\n");
    }/* end of for(count2) */

    fclose(read_file2);
  }

  fclose(read_file);

  /* terminating */
  free(filename);
}/* end of set_problem() */


void nn_read_test_pattern(){
  FILE *read_file;
  char filename[FGETS_LEN];
  char buff[FGETS_LEN];
  char c[2];
  int buff_i;
  int i;
  int count_x, count_y;

  /* initialize */
  fprintf(stdout,"filename? --> ");
  fflush(stdout);
  fgets(filename, FGETS_LEN, stdin);
  filename[ strlen(filename)-1 ] = '\0';
  if( filename == NULL ){
    fprintf(stdout,"# ERROR! fgets(filename=%s) was failed on nn_check().\n",filename);
    fprintf(stderr,"# ERROR! fgets(filename=%s) was failed on nn_check().\n",filename);
    exit(-1);
  }

  read_file = fopen(filename,"r");
  if( read_file == NULL ){
    fprintf(stdout,"# ERROR! fopen(%s) was failed  in nn_check().\n",filename);
fprintf(stderr,"# ERROR! fopen(%s) was failed  in nn_check().\n",filename);
    exit(-1);
  }

  /* read a correct answer, then its pattern */
  fflush(stdout);
  fgets(buff, sizeof(buff), read_file);
  buff_i = atoi(buff);
  for(i=0; i<OUTPUT; i++){
    if( i==buff_i ){
      correct[i] = ON;
    }else{
      correct[i] = OFF;
    }
  }
  print_correct();
  
  for(count_y=0; count_y<SIZE_Y; count_y++){
   fflush(stdout);
    fgets(buff, sizeof(buff), read_file);
    for(count_x=0; count_x<SIZE_X; count_x++){
      c[0] = *(buff + count_x);
      c[1] = '\0';
      if( atoi(c) == 1 ){
          test_pattern[(count_y*SIZE_X)+count_x] = ON;
          fprintf(stdout,"1");
      }else if( atoi(c) == 0 ){
          test_pattern[(count_y*SIZE_X)+count_x] = OFF;
          fprintf(stdout,"0");
      }else{
          fprintf(stderr,"#ERROR! atoi() reading from %s was failed.",filename);
          exit(1);
      }
}
    fprintf(stdout,"\n");
}
  test_pattern[SIZE_X*SIZE_Y] = ON; /* bias */

  fprintf(stdout,"CHECK filename %s\n",filename);
/* terminating */
  fclose(read_file);
}

