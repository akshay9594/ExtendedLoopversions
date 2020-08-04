



//Loop to be parallelized
for(int mybin = 0; mybin<mbins; mybin++) {
    const int start = mybin>0?binpos[mybin-1]:0;
    const int count = binpos[mybin] - start;
    for(int k=0; k<count; k++) {
	  const int new_i = start+k;
	  const int old_i = bins[mybin*atoms_per_bin+k];
	  new_x[new_i*PAD+0] = old_x[old_i*PAD+0];
	  new_x[new_i*PAD+1] = old_x[old_i*PAD+1];
	  new_x[new_i*PAD+2] = old_x[old_i*PAD+2];
	  new_v[new_i*PAD+0] = old_v[old_i*PAD+0];
	  new_v[new_i*PAD+1] = old_v[old_i*PAD+1];
	  new_v[new_i*PAD+2] = old_v[old_i*PAD+2];
	  new_type[new_i] = old_type[old_i];
    }
  }


//Initialization of binpos
  for(int i = 0; i < mbins; i++) {  
    binpos[i] = 0;
  }

int ix, iy, iz;

//First modification of binpos with function inlining
    for(int i = 0; i < nall; i++) {

  if(x[i * PAD] >= xprd)
    ix = (int)((x[i * PAD] - xprd) * bininvx) + nbinx - mbinxlo;
  else if(x[i * PAD]>= 0.0)
    ix = (int)(x[i * PAD] * bininvx) - mbinxlo;
  else
    ix = (int)(x[i * PAD] * bininvx) - mbinxlo - 1;

  if(x[i * PAD + 1] >= yprd)
    iy = (int)((x[i * PAD + 1] - yprd) * bininvy) + nbiny - mbinylo;
  else if(x[i * PAD + 1] >= 0.0)
    iy = (int)(x[i * PAD + 1] * bininvy) - mbinylo;
  else
    iy = (int)(x[i * PAD + 1] * bininvy) - mbinylo - 1;

  if(x[i * PAD + 2] >= zprd)
    iz = (int)((x[i * PAD + 2] - zprd) * bininvz) + nbinz - mbinzlo;
  else if(z >= 0.0)
    iz = (int)(x[i * PAD + 2] * bininvz) - mbinzlo;
  else
    iz = (int)(x[i * PAD + 2] * bininvz) - mbinzlo - 1;

      const int ibin = iz * mbiny * mbinx + iy * mbinx + ix + 1;

      if(binpos[ibin] < atoms_per_bin) {
    
        ac = binpos[ibin]++;

        bins[ibin * atoms_per_bin + ac] = i;
      } else resize = 1;
    }


//Second modification of binpos with function inlining
     for(int i=1; i<mbins; i++){
	   binpos[i] += binpos[i-1];
        if(copy_size<nmax) {
            free(x_copy);
            free(v_copy);
            free(type_copy);

            if(nmax * PAD == 0) 
                x_copy = NULL;
            else
                x_copy = (MMD_float*) malloc((nmax * PAD + 1024 + 1) * sizeof(MMD_float));
            
            if(nmax * PAD == 0) 
                v_copy = NULL;
            else
                v_copy = (MMD_float*) malloc((nmax * PAD + 1024 + 1) * sizeof(MMD_float));
                

            if(nmax == 0) type_copy = NULL;
            else type_copy = (int*) malloc((nmax) * sizeof(int));
        
            copy_size = nmax;
    
        }
     }