#include <hdf5.h>
#include <string.h>

#include "AtomData.hpp"
#include "writeSingleAtomData.hpp"

int writeSingleAtomData_pottxt(const char *fname, AtomData &atom)
{
  char gname[128];

  fout = open("fname", "w");

  fprintf(fout, "HEADER\n%.80s\n", &atom.header[0]);
  fprintf(fout, "Z\n%f\n", atom.ztotss);
  fprintf(fout, "ZCORE\n%f\n", atom.zcorss);
  fprintf(fout, "NSPIN\n%d\n", atom.nspin);
  fprintf(fout, "VDIF\n%f\n", atom.vdif);
  fprintf(fout, "ALAT\n%f\n", atom.ztotss);
  fprintf(fout, "EFERMI\n%f\n", atom.efermi);

  fprintf(fout, "XSTART\n%f\n", atom.xstart);
  fprintf(fout, "XMT\n%f\n", log(atom.rmt));
  fprintf(fout, "JMT\n%f\n", atom.jmt);
  fprintf(fout, "JWS\n%f\n", atom.jws);

  fprintf(fout, "NUMC\n%f\n", atom.numc);

  for(int ns=0; ns<atom.nspin; ns++)
  {
    fprintf(fout, "SPIN\n%d\n", ns);

    fprintf(fout, "RPOT\n");
    for(int i=0; i<atom.jmt; i++)
      fprintf(fout, "%20.13lf\n", atom.vr(i,ns));

    fprintf(fout, "V0\n%f\n", 0.0);

    // snprintf(gname,100,"rhotot%1d",ns+1);
    // write_vector<double>(loc_id,gname,&atom.rhotot(0,ns),atom.jws);
    if(atom.numc>0) // write core states if they exist
    {
      fprintf(fout, "CORE\n");
      fprintf(fout, "NC LC KC  EC\n");
      for(int i=0; i<atom.numc; i++)
        fprintf(fout, "%2d %2d %2d  %f\n", atom.nc(i,ns), atom.lc(i,ns), atom.kc(i,ns), atom.ec(i,ns));
    }
    fprintf(fout, "XVALWS\n%f\n", atom.xvalws[i]);
  }
  //  for(int j=0; j<100; j++) gname[j]=' ';
  //  write_vector<char>(loc_id,"JTitle",&gname[0],80);
  //  write_vector<double>(loc_id,"evec",&atom.evec[0],3);

  close(fout);
  return 0;
}
