
#ifndef EDFFILE_DEFINE
#define EDFFILE_DEFINE

#pragma once

#include "edf.h"
#include <mex.h>

#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

// samples structure
const int SampleFieldNumber= 8;
const unsigned int FullSampleFieldNumber= 29;

class CEDFSamples
{
public:
  CEDFSamples(void){ArrayAlreadyAllocated= false;};
  ~CEDFSamples(void){};

  void PrepareArrayStructure(unsigned int NewSamplesN);
  void AppendSample(FSAMPLE CurrentSample);
  
  void setFieldFlags(bool LoadFieldFlags[29]){for(unsigned int iF=0; iF<29;iF++) LoadField[iF]= LoadFieldFlags[iF];};
  mxArray* getMXArrayPointer(void){return Samples;};
  
  void Reset(void){ArrayAlreadyAllocated= false;};
  bool ArrayIsAllocated(void){return ArrayAlreadyAllocated;};
  
protected:
  void* SetField(unsigned int iField, mwSize FieldDim, mxClassID FieldType);
  void* SetScalarField(unsigned int iField, mxClassID FieldType);
  
  // service
  unsigned int SamplesN, iSample;
  unsigned int TotalFields;
  bool ArrayAlreadyAllocated;
  bool LoadField[29];
  mxArray* Samples;
  
  // fields pointers
  UINT32* FinalSamplesN; 
  UINT32* time;   // 0
  UINT16* flags;  // 1
  double *px, *py; // 2 3
  double *hx, *hy; // 4 5
  double *pa;      // 6 
  double *gx, *gy; // 7 8 
  double *rx, *ry; // 9 10
  UINT16 *status; // 11
  UINT16 *input;  // 12
  UINT16 *buttons;// 13
  INT16 *htype;   // 14
  INT16 *hdata;   // 15
  UINT16 *errors; // 16
  double *gxvel;   // 17 
  double *gyvel;   // 18 
  double *hxvel;   // 19
  double *hyvel;   // 20
  double *rxvel;   // 21
  double *ryvel;   // 22
  double *fgxvel;  // 23
  double *fgyvel;  // 24
  double *fhxvel;  // 25
  double *fhyvel;  // 26
  double *frxvel;  // 27
  double *fryvel;  // 28
};

class CEDFEvent: public FEVENT
{
public:
	CEDFEvent(){Message= "";};
	CEDFEvent(FEVENT Original);
	string Message;
};

class CEDFFile
{
public:
	CEDFFile(void){mexTrials= NULL;};
	~CEDFFile(void){};

	mxArray* Load(const char* Filename, unsigned char Options[3], bool SampleFieldsToLoad[29]);
  mxArray* ExportPreamble();
protected:
  // i/o
	EDFFILE* SourceFile;
  mxArray* mexTrials;

  // service info
	unsigned int TotalItems, TotalTrials;
  unsigned char flagLoadEvents, flagLoadSamples;
  unsigned char SampleFieldsToLoad[FullSampleFieldNumber];
  bool TrialIsOver;

  // Current trial info
  string Preamble;
	TRIAL Header;    
	vector <CEDFEvent>	Events;

  // Samples
  CEDFSamples SamplesClass;
	mxArray* Samples;
  unsigned int SamplesN, iSample;
  void* SampleFieldPointer[SampleFieldNumber];
  
	void LoadTrials(void);
  void LoadSingleTrial(unsigned int iTrial);
  void SaveSingleTrial(unsigned int iTrial);
  
	void AppendSample(FSAMPLE CurrentSample);
	void AppendEvent(FEVENT CurrentEvent);
  
  mxArray* ExportEDFInfo(TRIAL CurrentInfo);
  mxArray* ExportRecordings(RECORDINGS CurrentRecord);
  mxArray* ExportSamples(vector <FSAMPLE> CurrentSamples);
  mxArray* ExportEvents(vector <CEDFEvent> CurrentEvents);
 
  // service 
  void setMexRealFieldByNumber(mxArray *pm, mwIndex index, int fieldnumber, double Value);
};

#endif