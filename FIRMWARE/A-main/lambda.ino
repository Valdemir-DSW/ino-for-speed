int getlambda = analogRead(APlambda);
float voltogemin;
float voltogemax;
float auxvar;
void lambdamonit(){
  getlambda = analogRead(APlambda);
  if (Lbanda==0){
      if (getlambda < 1) {
        getlambda = 1;
      } else if (getlambda > 194) {
        getlambda = 194;
      }

      lambdaAFR =  (getlambda - 1.0f) * (2.0f- 0.0f) / (194.0f - 1.0f) + 0.0f;
    
  }else{
     voltogemin = (mvwb / 5.0) * 1023.0;
     voltogemax= (mavwb / 5.0) * 1023.0;
       if (getlambda < voltogemin) {
        getlambda = voltogemin;
      } else if (getlambda > voltogemax) {
        getlambda = voltogemax;
      }

      auxvar =  (getlambda - voltogemin) * (malwb - mlwb) / (voltogemax - voltogemin) + mlwb;
      lambdaAFR = auxvar / 14.7;
  } 


  
}
