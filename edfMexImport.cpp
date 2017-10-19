#include <mex.h>
#include <matrix.h>
#include <string.h>
#include "edf.h"

#include "EDFFile2.h"

CEDFFile EDFFile;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  mwSize OutputDims[]={1,2};

  // getting input 
  char Filename[2048];
  int FilenameLength= (mxGetM(prhs[0])*mxGetN(prhs[0]))+1;
  if (mxGetString(prhs[0], Filename, FilenameLength))
  {
    mexPrintf("Bad filename as a first argument\n");
    return;
  }
  
  // asking for help?
  if (!strcmp(Filename, "-help"))
  {
    mexPrintf("edfImport. Alexander Pastukhov. 2009\n");
    mexPrintf("Uploads information from EDF file in a trial-by-trial fashion\n");
    mexPrintf("Input:\n");
    mexPrintf("  Filename: edf filename WITH extension\n");
    mexPrintf("  EDF API flags: [consistency load_events load_samples], default [1 1 0]\n");
    mexPrintf("    consistency = 0 – no consistency check, 1 – check consistency and report, 2 – check consistency and fix.\n");
    mexPrintf("    load_events = 0 – do not load events, 1 – load events\n");
    mexPrintf("    load_samples = 0 – do not load samples, 1 – load sample\n");
    mexPrintf("  bool SampleFields[29]: marks which FSAMPLE structure fields to load. Default: all fields\n");
    mexPrintf("Output:\n");
    mexPrintf("  Trials: vector of trials, each trial contains\n");
    mexPrintf("    Header: see TRIAL structurine in EDF API manual\n");
    mexPrintf("    Samples: see FSAMPLE structurine in EDF API manual.\n");
    mexPrintf("    Events: see FEVENT structurine in EDF API manual\n");
    mexPrintf("  Preamble: file header, see EDF API manual\n");
  }
  
  // getting options
  unsigned char Options[3]= {1, 1, 0}; // default - check consistency and fix, load events, don't load samples
  unsigned char OptionLimits[3]= {2, 1, 1};
  if (nrhs>1)
  {
    mwSize OptionsDimN= mxGetNumberOfDimensions(prhs[1]);
    if (OptionsDimN!=2)
       mexErrMsgTxt("Bad options, see help for details");
    mwSize* OptionsDim= (mwSize*)mxGetDimensions(prhs[1]);
    
    if ((OptionsDim[0]==3 && OptionsDim[1]==1) || (OptionsDim[0]==1 && OptionsDim[1]==3))
    {
      double* OptionsFromMatlab= mxGetPr(prhs[1]);
      for(unsigned int iO= 0; iO<3; iO++)
      {
        Options[iO]= (unsigned char)OptionsFromMatlab[iO];
        if (Options[iO]>OptionLimits[iO])
          mexErrMsgTxt("Bad options, see help for details");
      }
    }
    else
       mexErrMsgTxt("Bad options, see help for details");
  }
  
  // getting/setting samples fields flags
  bool SampleFieldsToLoad[29];
  for(unsigned int iF= 0; iF<29; iF++)
    SampleFieldsToLoad[iF]= true;
  if (nrhs>2)
  {
    mwSize FlagsDimN= mxGetNumberOfDimensions(prhs[2]);
    if (FlagsDimN!=2)
       mexErrMsgTxt("Bad sample fields flags, see help for details");
    mwSize* FlagsDim= (mwSize*)mxGetDimensions(prhs[2]);
    
    if ((FlagsDim[0]==29 && FlagsDim[1]==1) || (FlagsDim[0]==1 && FlagsDim[1]==29))
    {
      double* FlagsFromMatlab= mxGetPr(prhs[2]);
      for(unsigned int iF= 0; iF<29; iF++)
        SampleFieldsToLoad[iF]= FlagsFromMatlab[iF];
    }
    else
       mexErrMsgTxt("Bad sample fields flags, see help for details");
  }
  SampleFieldsToLoad[11]= false; // never use "status" field

  
  // loading data into a structure
  plhs[0]= EDFFile.Load(Filename, Options, SampleFieldsToLoad);
	if (nlhs>1)
		plhs[1] = EDFFile.ExportPreamble();
}
