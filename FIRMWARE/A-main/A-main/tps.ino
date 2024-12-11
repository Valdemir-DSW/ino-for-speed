int signaltps = 0;


void tpshande(){
 signaltps = analogRead(APtps);
 

  if (signaltps < tpsmin) {
    signaltps = tpsmin;
  } else if (signaltps > tpsmax) {
    signaltps = tpsmax;
  }

  tpsPosition =  (signaltps - tpsmin) * (100 - 0) / (tpsmax - tpsmin) + 0;
  
}
