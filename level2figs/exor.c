  if( err < MIN_ERR ){ 
    fprintf(stdout,"FINISH 2: iteration = %4d, error = %.10f\n",ite,err); 
  }else if( ite <= ITERATIONS ){ 
    fprintf(stdout,"FINISH 1: iteration = %4d, error = %.10f\n",ite,err); 
