#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "parameter.h"

#define	drand() ((double)(random()+1)/RAND_MAX-0.5)

#define sq(x) ((x)*(x))

/* global variables */
int ite;          /* 試行回数 */
double err;
double sum[CTG];
double sum_error[CTG];
double 	i_lay[CTG][INPUT+1],
		h_lay[HIDDEN+1],
		o_lay[OUTPUT],
		teach[CTG][OUTPUT];
double  test_pattern[INPUT+1],
		correct[OUTPUT]; /* to check nn with test-pattern */
double	ih_w[INPUT+1][HIDDEN],
		ho_w[HIDDEN+1][OUTPUT];
double	h_del[HIDDEN],
		o_del[OUTPUT];
double  ih_dw[INPUT+1][HIDDEN],
		ho_dw[HIDDEN+1][OUTPUT];

extern double sigmoid(double s);
extern void set_problem();
extern void nn_read_test_pattern();

void print_teach(int index);
void print_correct();
void nn_learn();
void nn_eval();
void nn_check();
void usage();
void usage2();
void terminate();

int main(int argc, char **argv)
{
  int	i,j;
  char buff[FGETS_LEN];
  char command;
  int final_flag;
  int seed;

  if( argc != 2 ){
    usage();
  }else{
    seed = atoi(argv[1]);
    srandom((int)seed);
    random();
  }

 
  /* read & set test-case */
  set_problem();
  
  /* initialize */
  h_lay[HIDDEN]=ON;
  for(j=0;j<HIDDEN;j++)
    for(i=0;i<=INPUT;i++){
      ih_w[i][j]=WD*drand();
      ih_dw[i][j]=0.;
    }
  for(j=0;j<OUTPUT;j++)
    for(i=0;i<=HIDDEN;i++){
      ho_w[i][j]=WD*drand();
      ho_dw[i][j]=0.;
    }
  ite = 1;
  final_flag = 0;

  usage2();

  for(;;){ // 終了コマンド 'q' が入力されるまで繰り返す

    // コマンド読み取り
    fflush(stdout);
    strncpy(&command,buff,1);

    // 指定されたコマンドに対する処理を実行
    //   l(learn): 学習
    //   c(check): 学習事例を用いた学習度合いの確認
    //   e(evaluate): 未知パターンを用いた評価
    //   q(quit): 終了
    //   h(help): ヘルプ
    command = 'l';

    switch( command ){
      case 'l': /* learning */
	nn_learn();
	final_flag = 1;
	break;
      case 'c': /* check with learned-pattern */
	nn_check();
	break;
      case 'e': /* evaluation with other-pattern */
	nn_read_test_pattern();
	nn_eval();
	break;
      case 'q': /* quit */
	final_flag = 1;
	break;
      case 'h': /* help */
	usage2();
	/* continue below */
      default:
	break;
    }
    
    

    if( final_flag == 1 ){
      break;
    }
  }

  return 0;
}


void nn_learn(){
  int i, j, ctg;
  int start_ite;

  /* reset result variables */
  for(ctg=0; ctg<CTG; ctg++){
    sum[ctg] = 0.0;
    sum_error[ctg] = 0.0;
  }
  start_ite = ite;
  //  fprintf(stdout,"\n");

  /* learning */
  for(; ite<=(start_ite+ITERATIONS-1); ite++){
    for(ctg=0,err=0.;ctg<CTG;ctg++){
      for(j=0;j<HIDDEN;j++){
	for(i=0,sum[ctg]=0.;i<=INPUT;i++)
	  sum[ctg] += i_lay[ctg][i]*ih_w[i][j];
	h_lay[j]=sigmoid(sum[ctg]);
      }
      for(j=0;j<OUTPUT;j++){
	for(i=0,sum[ctg]=0.;i<=HIDDEN;i++)
	  sum[ctg]+=h_lay[i]*ho_w[i][j];
	o_lay[j]=sigmoid(sum[ctg]);
      }
      for(i=0;i<OUTPUT;i++){
	err+=sq(teach[ctg][i]-o_lay[i])/2./(double)CTG;
	o_del[i]=(teach[ctg][i]-o_lay[i])*o_lay[i]*(1.-o_lay[i]);
      }
      for(j=0;j<=HIDDEN;j++){
	h_del[j]=0.;
	for(i=0;i<OUTPUT;i++)
	  h_del[j]+=o_del[i]*ho_w[j][i];
	h_del[j]*=h_lay[j]*(1.-h_lay[j]);
      }
      
      for(j=0;j<=HIDDEN;j++)
	for(i=0;i<OUTPUT;i++){
	  ho_dw[j][i]=ETA*o_del[i]*h_lay[j]+ALPHA*ho_dw[j][i];
	  ho_w[j][i]+=ho_dw[j][i];
	  //ho_w[j][i]+=ETA*o_del[i]*h_lay[j];
	}
      for(j=0;j<=INPUT;j++)
	for(i=0;i<HIDDEN;i++){
	  ih_dw[j][i]=ETA*h_del[i]*i_lay[ctg][j]+ALPHA*ih_dw[j][i];
	  ih_w[j][i]+=ih_dw[j][i];
	  //ih_w[j][i]+=ETA*h_del[i]*i_lay[ctg][j];
	}
    }
    if( err <= MIN_ERR ) break;

    //printf("iteration = %4d error = %.10f\n",ite,err);
  }
  printf("%4d\n",ite);
}/* end of nn_learn() */


void nn_check(){
  int i, j, ctg;

  fprintf(stdout,"err=%lf, MIN_ERR=%lf\n",err,MIN_ERR);
  for(ctg=0;ctg<CTG;ctg++){
    fprintf(stdout,"CHECK ctg[%d] : \n",ctg);
    for(i=0;i<INPUT;i++)
      //fprintf(stdout,"i[%d] = %1.1f  ",i,i_lay[ctg][i]);
      for(j=0;j<HIDDEN;j++){
	for(i=0,sum[ctg]=0.;i<=INPUT;i++)
	  sum[ctg]+=i_lay[ctg][i]*ih_w[i][j];
	h_lay[j]=sigmoid(sum[ctg]);
      }
    for(j=0;j<OUTPUT;j++){
      for(i=0,sum[ctg]=0.;i<=HIDDEN;i++)
	sum[ctg]+=h_lay[i]*ho_w[i][j];
      o_lay[j]=sigmoid(sum[ctg]);
      sum_error[ctg] += fabs( o_lay[j] - teach[ctg][j] );
      fprintf(stdout,"CHECK o[%d] = %1.5f, t[%d] = %1.1f\n",j,o_lay[j],j,teach[ctg][j]);
    }
    fprintf(stdout,"CHECK sum_error = %1.5f\n",sum_error[ctg]);
    sum_error[ctg] = 0.0;
  }
  //fprintf(stdout,"iteration = %4d, error = %1.5f\n",ite,err);
}/* end of nn_check() */


void nn_eval(){
  int i, j;
  double l_sum, l_sum_error;

  l_sum = l_sum_error = 0.0;
  for(i=0;i<INPUT;i++)
    for(j=0;j<HIDDEN;j++){
      for(i=0,l_sum=0.;i<=INPUT;i++)
	l_sum+=test_pattern[i]*ih_w[i][j];
      h_lay[j]=sigmoid(l_sum);
    }
  for(j=0;j<OUTPUT;j++){
    for(i=0,l_sum=0.;i<=HIDDEN;i++)
      l_sum+=h_lay[i]*ho_w[i][j];
    o_lay[j]=sigmoid(l_sum);
    l_sum_error += fabs( o_lay[j] - correct[j] );
    fprintf(stdout,"EVA o[%d] = %1.5f, correct[%d] = %1.1f\n",j,o_lay[j],j,correct[j]);
  }
  fprintf(stdout,"EVA sum_error = %1.5f\n",l_sum_error);
/* end of nn_eval() */
}


void usage(){
  fprintf(stderr," Usage: prompt> ./a.out random-seed\n");
  exit(0);
}


void usage2(){
  /*
  fprintf(stdout,"  ===== USAGE =====\n");
  fprintf(stdout,"  learn: nn> l\n");
  fprintf(stdout,"  check: nn> c\n");
  fprintf(stdout,"  evaluation: nn> e\n");
  fprintf(stdout,"       after that, input filename defined test-pattern\n");
  fprintf(stdout,"  =================\n");
  */
}


void print_teach(int index){
  int i;
  //  fprintf(stdout,"teach[%d] = ",index);
  for(i=0; i<OUTPUT; i++){
      if( teach[index][i] == ON ){
	//      fprintf(stdout,"1");
      }else{
	// fprintf(stdout,"0");
      }
  }
  // fprintf(stdout,"\n");
}


void print_correct(){
  int i;
    fprintf(stdout,"correct = ");
  for(i=0; i<OUTPUT; i++){
      if( correct[i] == ON ){
	      fprintf(stdout,"1");
      }else if( correct[i] == OFF ){
	 fprintf(stdout,"0");
      }else{
	 fprintf(stderr,"#ERROR! correct[%d]=%f has wrong value.",i,correct[i]);
          exit(1);
      }
  }
   fprintf(stdout,"\n");
}
