
//Loop to parallelize from subroutine 'clincs'
 for(b=0;b<ncons;b++) {
    tmp0=r[b][0];
    tmp1=r[b][1];
    tmp2=r[b][2];
    len=bllen[b];
    i=bla1[b];
    j=bla2[b];
    for(n=blnr[b];n<blnr[b+1];n++) {
      k=blbnb[n];
      blm[n]=blcc[n]*(tmp0*r[k][0]+tmp1*r[k][1]+tmp2*r[k][2]); 
    } 
    mvb=blc[b]*(tmp0*(xp[i][0]-xp[j][0])+
		tmp1*(xp[i][1]-xp[j][1])+    
		tmp2*(xp[i][2]-xp[j][2])-len);
    rhs1[b]=mvb;
    sol[b]=mvb;
    
  }

  //Loop that fills in the subscript array 'blnr' from subroutine 'init_lincs'

    blnr[0] = 0;
    nZeroLen = 0;
    for(i=0; (i<ncons); i++) {
      j=3*i;
      a1=iatom[j+1];
      a2=iatom[j+2];
      /* (*blnr)[i+1] = (*blnr)[i] + at_cn[a1] + at_cn[a2] - 2; */
      type=iatom[j];
      len =idef->iparams[type].shake.dA;
      len1=idef->iparams[type].shake.dB;
      if (( len<GMX_REAL_MIN || len1<GMX_REAL_MIN) && 
	  fabs(len1-len)>GMX_REAL_MIN)
	  fatal_error(0,"It is not allowed to have a constraint length "
		    "zero and non-zero in the A and B topology");
      if (len < GMX_REAL_MIN)
	    nZeroLen++;

      bla1[i]=a1;
      bla2[i]=a2;
      bllen[i]=len;
      bllen0[i]=len;
      ddist[i]=len1-len;
      im1=md->invmass[a1];
      im2=md->invmass[a2];
      blc[i]=(1.0f/sqrt(im1+im2))
     
      blnr[i+1]=(*blnr)[i];
      for(k=0; k<at_cn[a1-start]; k++){
	    if (at_c[a1-start][k] != i)
	        blbnb[blnr[i+1]++]=at_c[a1-start][k];
      }
      
      for(k=0; k<at_cn[a2-start]; k++){
	    if (at_c[a2-start][k] != i)
	        blbnb[blnr[i+1]++]=at_c[a2-start][k];
      }
      
      qsort(&(blbnb[blnr[i]]),blnr[i+1]-blnr[i],    //Built-in function
            sizeof(blbnb[0]),int_comp);
    }