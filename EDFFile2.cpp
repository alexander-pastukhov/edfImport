#include "EDFFile2.h"

void* CEDFSamples::SetField(unsigned int iField, mwSize FieldDim, mxClassID FieldType)
{
  mwSize FieldDims[2]= {1, 1};
  FieldDims[0]= FieldDim;
  FieldDims[1]= SamplesN;
  mxArray* TempArrayPointer= mxCreateNumericArray(2, FieldDims, FieldType, mxREAL);
  mxSetFieldByNumber(Samples, 0, iField, TempArrayPointer);
  return (void*)mxGetPr(TempArrayPointer);
}

void* CEDFSamples::SetScalarField(unsigned int iField, mxClassID FieldType)
{
  mwSize FieldDims[2]= {1, 1};
  mxArray* TempArrayPointer= mxCreateNumericArray(2, FieldDims, FieldType, mxREAL);
  mxSetFieldByNumber(Samples, 0, iField, TempArrayPointer);
  return (void*)mxGetPr(TempArrayPointer);
}


void CEDFSamples::PrepareArrayStructure(unsigned int NewSamplesN)
{
  const char *FullSampleFieldNames[FullSampleFieldNumber]=    {"time", "flags", "px", "py", "hx",  "hy", "pa",   "gx", "gy", "rx", "ry", "status", "input", "buttons", "htype", "hdata", "errors", "gxvel", "gyvel", "hxvel", "hyvel", "rxvel", "ryvel", "fgxvel", "fgyvel", "fhxvel", "fhyvel", "frxvel", "fryvel"};

  // copying samples number
  SamplesN= NewSamplesN;
  iSample= 0;
  
  // computing number of selected fields
  TotalFields= 0;
  unsigned int FieldIndex[FullSampleFieldNumber];
  for(unsigned int iF= 0; iF<FullSampleFieldNumber; iF++)
    if (LoadField[iF])
    {
      FieldIndex[TotalFields]= iF;
      TotalFields++;
    }
  
  // allocating the arrays
  char** SelectedSampleFieldNames= new char*[TotalFields+1];
  
  // preparing selected fields names
  SelectedSampleFieldNames[0]= new char[strlen("RealNumberOfSamples")+1];
  strcpy(SelectedSampleFieldNames[0], "RealNumberOfSamples");
  for(unsigned int iF= 0; iF<TotalFields; iF++)
  {
    SelectedSampleFieldNames[iF+1]= new char[strlen(FullSampleFieldNames[FieldIndex[iF]])+1];
    strcpy(SelectedSampleFieldNames[iF+1], FullSampleFieldNames[FieldIndex[iF]]);
  }
  
  // creating a structure
  mwSize SampleDims[2]= {1, 1};
  Samples=  mxCreateStructArray(2, SampleDims, TotalFields+1, (const char**)SelectedSampleFieldNames);
  
  // deleting field names array
  for(unsigned int iF= 0; iF<TotalFields; iF++)
    delete [] SelectedSampleFieldNames[iF];
  delete [] SelectedSampleFieldNames;
  
  // creating field value holders
  unsigned int iF= 0;

  // time
  FinalSamplesN= (UINT32*)SetScalarField(iF++, mxUINT32_CLASS);
  time= LoadField[0] ? (UINT32*)SetField(iF++, 1, mxUINT32_CLASS) : NULL;
  flags= LoadField[1] ? (UINT16*)SetField(iF++, 1, mxUINT16_CLASS) : NULL;
  px= LoadField[2] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  py= LoadField[3] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  hx= LoadField[4] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  hy= LoadField[5] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  pa= LoadField[6] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  gx= LoadField[7] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  gy= LoadField[8] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  rx= LoadField[9] ? (double*)SetField(iF++, 1,  mxDOUBLE_CLASS) : NULL;
  ry= LoadField[10] ? (double*)SetField(iF++, 1,  mxDOUBLE_CLASS) : NULL;
  //status= LoadField[11] ? (UINT16*)SetField(iF++, 1, mxUINT16_CLASS) : NULL;
  input= LoadField[12] ? (UINT16*)SetField(iF++, 1, mxUINT16_CLASS) : NULL;
  buttons= LoadField[13] ? (UINT16*)SetField(iF++, 1, mxUINT16_CLASS) : NULL;
  htype= LoadField[14] ? (INT16*)SetField(iF++, 1, mxINT16_CLASS) : NULL;
  hdata= LoadField[15] ? (INT16*)SetField(iF++, 8, mxINT16_CLASS) : NULL;
  errors= LoadField[16] ? (UINT16*)SetField(iF++, 1, mxUINT16_CLASS) : NULL;
  gxvel= LoadField[17] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  gyvel= LoadField[18] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  hxvel= LoadField[19] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  hyvel= LoadField[20] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  rxvel= LoadField[21] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  ryvel= LoadField[22] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  fgxvel= LoadField[23] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  fgyvel= LoadField[24] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  fhxvel= LoadField[25] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  fhyvel= LoadField[26] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  frxvel= LoadField[27] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  fryvel= LoadField[28] ? (double*)SetField(iF++, 2,  mxDOUBLE_CLASS) : NULL;
  
  ArrayAlreadyAllocated= true;
}

void CEDFSamples::AppendSample(FSAMPLE CurrentSample)
{
  FinalSamplesN[0]= iSample+1;
  if (iSample>=SamplesN)
  {
    mexPrintf("Miscalculated number of samples. Current sample (%d) is over the calculated limit of %d!\n", iSample, SamplesN);
    return;
  }

  // copying 1-element fields
  if (LoadField[0]) time[iSample]= CurrentSample.time;
  if (LoadField[1]) flags[iSample]= CurrentSample.flags;
  if (LoadField[9]) rx[iSample]= CurrentSample.rx;
  if (LoadField[10]) ry[iSample]= CurrentSample.ry;
  //if (LoadField[11]) status[iSample]= CurrentSample.status;
  if (LoadField[12]) input[iSample]= CurrentSample.input;
  if (LoadField[13]) buttons[iSample]= CurrentSample.buttons;
  if (LoadField[14]) htype[iSample]= CurrentSample.htype;
  if (LoadField[16]) errors[iSample]= CurrentSample.errors;
  
  // copying 2-element fields
  for(unsigned int iDim= 0; iDim<2; iDim++)
  {
    if (LoadField[2]) px[iDim+iSample*2]= CurrentSample.px[iDim];
    if (LoadField[3]) py[iDim+iSample*2]= CurrentSample.py[iDim];
    if (LoadField[4]) hx[iDim+iSample*2]= CurrentSample.hx[iDim];
    if (LoadField[5]) hy[iDim+iSample*2]= CurrentSample.hy[iDim];
    if (LoadField[6]) pa[iDim+iSample*2]= CurrentSample.pa[iDim];
    if (LoadField[7]) gx[iDim+iSample*2]= CurrentSample.gx[iDim];
    if (LoadField[8]) gy[iDim+iSample*2]= CurrentSample.gy[iDim];
    if (LoadField[17]) gxvel[iDim+iSample*2]= CurrentSample.gxvel[iDim];
    if (LoadField[18]) gyvel[iDim+iSample*2]= CurrentSample.gyvel[iDim];
    if (LoadField[19]) hxvel[iDim+iSample*2]= CurrentSample.hxvel[iDim];
    if (LoadField[20]) hyvel[iDim+iSample*2]= CurrentSample.hyvel[iDim];
    if (LoadField[21]) rxvel[iDim+iSample*2]= CurrentSample.rxvel[iDim];
    if (LoadField[22]) ryvel[iDim+iSample*2]= CurrentSample.ryvel[iDim];
    if (LoadField[23]) fgxvel[iDim+iSample*2]= CurrentSample.fgxvel[iDim];
    if (LoadField[24]) fgyvel[iDim+iSample*2]= CurrentSample.fgyvel[iDim];
    if (LoadField[25]) fhxvel[iDim+iSample*2]= CurrentSample.fhxvel[iDim];
    if (LoadField[26]) fhyvel[iDim+iSample*2]= CurrentSample.fhyvel[iDim];
    if (LoadField[27]) frxvel[iDim+iSample*2]= CurrentSample.frxvel[iDim];
    if (LoadField[28]) fryvel[iDim+iSample*2]= CurrentSample.fryvel[iDim];
  }
  
  // copying an 8-element field
  for(unsigned int iDim= 0; iDim<8; iDim++)
    if (LoadField[15]) hdata[iDim+iSample*8]= CurrentSample.hdata[iDim];

  iSample++;  
}

// ------ CEDFFile ------------------------------------------------------------------
mxArray* CEDFFile::Load(const char* Filename, unsigned char Options[3], bool SampleFieldsToLoad[29])
{
  // saving options
  flagLoadEvents= Options[1];
  flagLoadSamples= Options[2];
  SamplesClass.setFieldFlags(SampleFieldsToLoad);
  
	// opening source file
	int ReturnValue;
	SourceFile= edf_open_file(Filename, Options[0], Options[1], Options[2], &ReturnValue);
	if (SourceFile==NULL)
	{
    char Msg[1024];
// char *errmsg = eyelink_get_error(ReturnValue ,"edf_open_file");
    sprintf(Msg, "Failed to open file %s. Error %d\n", Filename, ReturnValue);
    mexErrMsgTxt(Msg);
	}
  
  // first getting data as a work around the EDF API bug
  edf_get_next_data(SourceFile);
  edf_get_float_data(SourceFile);
	ALLF_DATA* CurrentData;
	int DataType;
	for(DataType= edf_get_next_data(SourceFile); DataType!=NO_PENDING_ITEMS; DataType= edf_get_next_data(SourceFile))
	{
		CurrentData= edf_get_float_data(SourceFile);
		if (DataType==SAMPLE_TYPE)
		{
// 			mexPrintf("  Time field stamp of the first sample in the file: %d\n", CurrentData->fs.time);
// 			mexEvalString("drawnow");
			break;
		}
	}

  // Loading data trial by trial
  LoadTrials();
  
  // get preamble text
	int PreambleLength= edf_get_preamble_text_length(SourceFile);
	if (PreambleLength>0)
	{
		char* PreambleChar= new char[PreambleLength+1];
		ReturnValue= edf_get_preamble_text(SourceFile, PreambleChar, PreambleLength);
		Preamble= PreambleChar;
		delete [] PreambleChar;
	}

  // closing file
	edf_close_file(SourceFile);
	
  return mexTrials;
}

void CEDFFile::LoadTrials(void)
{
	// setting up trial navigation
	if (edf_set_trial_identifier(SourceFile, "TRIALID", "TRIAL OK"))
    mexErrMsgTxt("Failed to set up trial navigation identifier");
	TotalTrials= edf_get_trial_count(SourceFile);
  
  // trial structure
  const int TrialFieldNumber= 3;
  const char *TrialFieldNames[TrialFieldNumber]= {"Header", "Samples", "Events"};

  // allocating output array
  mwSize TrialDims[]={1,2};
  TrialDims[1]= TotalTrials;
  mexTrials= mxCreateStructArray(2, TrialDims, TrialFieldNumber, TrialFieldNames);

  // loop through trials
  unsigned int TotalSteps= TotalTrials;
  double Step= 1.0;
  if (TotalSteps>10)
  {
    TotalSteps= 10;
    Step= (double)TotalTrials/(double)TotalSteps;
  }
  double CurrentStep= Step;
  unsigned int iBar= 1;
  mexPrintf("Loading %d trials [|", TotalTrials);
  for(unsigned int iSpace= 0; iSpace<TotalSteps-1; iSpace++)
    mexPrintf(" ");
  mexPrintf("]");
  mexEvalString("drawnow");
  
	for(unsigned int iTrial= 0; iTrial<TotalTrials; iTrial++)
	{
    // progress bar
    if (iTrial>=CurrentStep)
    {
      CurrentStep= CurrentStep+Step;
      iBar++;
      // erasing previous errorbars
      mexPrintf("\b");
      for(unsigned int iSpace= 0; iSpace<TotalSteps; iSpace++)
          mexPrintf("\b");
      
      for(unsigned int iSpace= 0; iSpace<TotalSteps; iSpace++)
      {
        if (iSpace<iBar)
          mexPrintf("|");
        else
          mexPrintf(" ");
      }
      mexPrintf("]");
      mexEvalString("drawnow");
    }
    
    LoadSingleTrial(iTrial);
 		SaveSingleTrial(iTrial);
	}
  mexPrintf("\n");
}

void CEDFFile::LoadSingleTrial(unsigned int iTrial)
{
	// navigating to the current trial
	int JumpResults= edf_jump_to_trial(SourceFile, iTrial);
   
  // obtaining its header
	int GoodJump= edf_get_trial_header(SourceFile, &Header);
  mxSetFieldByNumber(mexTrials, iTrial, 0, ExportEDFInfo(Header));

	// clearing arrays
  SamplesClass.Reset();
  Events.clear();

  // samples/events data holders
  ALLF_DATA* CurrentData;
	int DataType;

	// getting data
  TrialIsOver= false;
  UINT32 CurrentTime;
	for(DataType= edf_get_next_data(SourceFile); DataType!=NO_PENDING_ITEMS && !TrialIsOver; DataType= edf_get_next_data(SourceFile))
	{
		// obtaining actual data
 		CurrentData= edf_get_float_data(SourceFile);
    switch(DataType) 
    {
    case SAMPLE_TYPE:
      CurrentTime= CurrentData->fs.time;
      AppendSample(CurrentData->fs);
      break;
    case STARTPARSE:
    case ENDPARSE:
    case BREAKPARSE:
    case STARTBLINK :
    case ENDBLINK:
    case STARTSACC:
    case ENDSACC:
    case STARTFIX:
    case ENDFIX:
    case FIXUPDATE:
    case MESSAGEEVENT:
    case STARTSAMPLES:
    case ENDSAMPLES:
    case STARTEVENTS:
    case ENDEVENTS:
      CurrentTime= CurrentData->fe.sttime;
      if (CurrentTime>Header.endtime)
      {
        TrialIsOver= true;
        break;
      }
      AppendEvent(CurrentData->fe);
      break;
    case BUTTONEVENT:
    case INPUTEVENT:
    case LOST_DATA_EVENT:
      CurrentTime= CurrentData->fe.sttime;
    	if (CurrentTime>Header.endtime)
      {
        TrialIsOver= true;
        break;
      }
      AppendEvent(CurrentData->fe);
      break;
    case RECORDING_INFO:
      CurrentTime= CurrentData->fe.time;
      //AppendRecordingInfo(CurrentData->rec);
      break;
    default:
      CurrentTime= CurrentData->fe.time;
		}
    
    //mexPrintf("%d\n", CurrentTime);
    
    // end of trial check
    if (CurrentTime>Header.endtime)
  break;
  }
}
  
void CEDFFile::SaveSingleTrial(unsigned int iTrial)
{
  mxSetFieldByNumber(mexTrials, iTrial, 1, SamplesClass.getMXArrayPointer());
  mxSetFieldByNumber(mexTrials, iTrial, 2, ExportEvents(Events));
}
  
void CEDFFile::AppendSample(FSAMPLE CurrentSample)
{
  // if we have not allocated array yet, should do now!
  if (!SamplesClass.ArrayIsAllocated())
  {
    // computing total number of samples
    SamplesN= (unsigned int)((Header.endtime)-CurrentSample.time+1)/(1000/Header.rec->sample_rate);
    SamplesClass.PrepareArrayStructure(SamplesN);
  }
  
  SamplesClass.AppendSample(CurrentSample);
  
  if (iSample>=SamplesN)
    mexPrintf("Over the limit %d (max %d)!\n", iSample, SamplesN);
}

void CEDFFile::AppendEvent(FEVENT CurrentEvent)
{
	CEDFEvent ConvertedEvent(CurrentEvent);
  if (ConvertedEvent.Message=="TRIAL OK")
    TrialIsOver= true;
	Events.push_back(ConvertedEvent);
}

mxArray* CEDFFile::ExportEDFInfo(TRIAL CurrentInfo)
{
  // defining info structure
  const int InfoFieldNumber= 4;
  const char *InfoFieldNames[InfoFieldNumber]= {"rec", "duration", "starttime", "endtime"};
  const mxClassID InfoFieldType[InfoFieldNumber]= {mxINT8_CLASS, mxUINT32_CLASS, mxUINT32_CLASS, mxUINT32_CLASS};
  mwSize InfoDims[2]= {1, 1};
  mxArray* mexInfo=  mxCreateStructArray(2, InfoDims, InfoFieldNumber, InfoFieldNames);

 // creating field value holders
  mwSize FieldDims[2]= {1, 1};
  UINT32* InfoFieldPointer[InfoFieldNumber];
  for(int iField= 1; iField<InfoFieldNumber; iField++)
  {
    FieldDims[0]= 1;
    FieldDims[1]= 1;
    mxArray* CurrentFieldMexPointer= mxCreateNumericArray(2, FieldDims, InfoFieldType[iField], mxREAL);
    mxSetFieldByNumber(mexInfo, 0, iField, CurrentFieldMexPointer);
    InfoFieldPointer[iField]= (UINT32*)mxGetPr(CurrentFieldMexPointer);
  }

  // copying timing data
  InfoFieldPointer[1][0]= CurrentInfo.duration;
  InfoFieldPointer[2][0]= CurrentInfo.starttime;
  InfoFieldPointer[3][0]= CurrentInfo.endtime;
  
  // copying recordings structure
  mxSetFieldByNumber(mexInfo, 0, 0, ExportRecordings(*CurrentInfo.rec));
 
  return mexInfo;
}

mxArray* CEDFFile::ExportRecordings(RECORDINGS CurrentRecord)
{
  // defining info structure
  const int RecordFieldNumber= 9;
  const char *RecordFieldNames[RecordFieldNumber]= {"time",    "state",    "record_type", "pupil_type", "recoding_mode", "filter_type", "sample_rate", "pos_type", "eye"};
  const mxClassID RecordFieldType[RecordFieldNumber]= {mxUINT32_CLASS, mxINT8_CLASS,  mxINT8_CLASS,  mxINT8_CLASS,  mxINT8_CLASS,   mxINT8_CLASS, mxDOUBLE_CLASS, mxINT8_CLASS, mxINT8_CLASS};
  
  mwSize RecordDims[2]= {1, 1};
  mxArray* mexRecord=  mxCreateStructArray(2, RecordDims, RecordFieldNumber, RecordFieldNames);
  
 // creating field value holders
  mwSize FieldDims[2]= {1, 1};
  void* RecordFieldPointer[RecordFieldNumber];
  for(int iField= 0; iField<RecordFieldNumber; iField++)
  {
    mxArray* CurrentFieldMexPointer= mxCreateNumericArray(2, FieldDims, RecordFieldType[iField], mxREAL);
    mxSetFieldByNumber(mexRecord, 0, iField, CurrentFieldMexPointer);
    RecordFieldPointer[iField]= (void*)mxGetPr(CurrentFieldMexPointer);
  }
  
//   // copying data
  ((UINT32*)RecordFieldPointer[0])[0]= CurrentRecord.time;
  ((byte*)RecordFieldPointer[1])[0]= CurrentRecord.state;
  ((byte*)RecordFieldPointer[2])[0]= CurrentRecord.record_type;
  ((byte*)RecordFieldPointer[3])[0]= CurrentRecord.pupil_type;
  ((byte*)RecordFieldPointer[4])[0]= CurrentRecord.recording_mode;
  ((byte*)RecordFieldPointer[5])[0]= CurrentRecord.filter_type;
  ((double*)RecordFieldPointer[6])[0]= CurrentRecord.sample_rate;
  ((byte*)RecordFieldPointer[7])[0]= CurrentRecord.pos_type;
  ((byte*)RecordFieldPointer[8])[0]= CurrentRecord.eye;
  
  return mexRecord;
}


mxArray* CEDFFile::ExportEvents(vector <CEDFEvent> CurrentEvents)
{
  // defining info structure
  const int EventFieldNumber= 35;
  const char *EventFieldNames[EventFieldNumber]= {"time", "type", "read", "eye", "sttime", "entime", "hstx", "hsty", "gstx", "gsty", "sta",  
  "henx", "heny", "genx", "geny", "ena", "havx", "havy", "gavx", "gavy", "ava", "avel", 
  "pvel", "svel", "evel", "supd_x", "eupd_x", "supd_y", "eupd_y", "status", "flags",
  "input", "buttons", "parsedby", "message"}; 
  const mxClassID EventFieldType[EventFieldNumber]= {mxUINT32_CLASS, mxUINT16_CLASS, mxUINT16_CLASS, mxUINT16_CLASS,  mxUINT32_CLASS, mxUINT32_CLASS,
   mxDOUBLE_CLASS, mxDOUBLE_CLASS, mxDOUBLE_CLASS, mxDOUBLE_CLASS, mxDOUBLE_CLASS, mxDOUBLE_CLASS, mxDOUBLE_CLASS,
   mxDOUBLE_CLASS, mxDOUBLE_CLASS, mxDOUBLE_CLASS, mxDOUBLE_CLASS, mxDOUBLE_CLASS, mxDOUBLE_CLASS, mxDOUBLE_CLASS,
   mxDOUBLE_CLASS, mxDOUBLE_CLASS, mxDOUBLE_CLASS, mxDOUBLE_CLASS, mxDOUBLE_CLASS, mxDOUBLE_CLASS, mxDOUBLE_CLASS,
   mxDOUBLE_CLASS, mxDOUBLE_CLASS, mxUINT16_CLASS, mxUINT16_CLASS, mxUINT16_CLASS, mxUINT16_CLASS, mxUINT16_CLASS, mxSINGLE_CLASS};
  mwSize EventDims[2]= {1, 1};
  mxArray* mexEvent=  mxCreateStructArray(2, EventDims, EventFieldNumber, EventFieldNames);
  
  // creating field value holders
  mxArray* EventFieldMexPointer[EventFieldNumber];
  void* EventFieldPointer[EventFieldNumber-1];
  mwSize FieldDims[2]= {1, 1};
  for(int iField= 0; iField<EventFieldNumber-1; iField++)
  {
    FieldDims[1]= CurrentEvents.size();
    mxArray* EventFieldMexPointer= mxCreateNumericArray(2, FieldDims, EventFieldType[iField], mxREAL);
    EventFieldPointer[iField]= (void*)mxGetPr(EventFieldMexPointer);
    mxSetFieldByNumber(mexEvent, 0, iField, EventFieldMexPointer);
  }
  
  // special case: string
  mwSize EventStringDims[2]= {1, 1};
  EventStringDims[1]= CurrentEvents.size();
  mxArray* StringFieldMexPointer= mxCreateCellArray(2, EventStringDims);
  mxSetFieldByNumber(mexEvent, 0, 34, StringFieldMexPointer);
  
  // copying data
  for(int iEvent= 0; iEvent<CurrentEvents.size(); iEvent++)
  {
 ((UINT32*)EventFieldPointer[0])[iEvent]= CurrentEvents[iEvent].time;
 ((INT16*)EventFieldPointer[1])[iEvent]= CurrentEvents[iEvent].type;
 ((UINT16*)EventFieldPointer[2])[iEvent]= CurrentEvents[iEvent].read;
 ((INT16*)EventFieldPointer[3])[iEvent]= CurrentEvents[iEvent].eye;
 ((UINT32*)EventFieldPointer[4])[iEvent]= CurrentEvents[iEvent].sttime;
 ((UINT32*)EventFieldPointer[5])[iEvent]= CurrentEvents[iEvent].entime;
 ((double*)EventFieldPointer[6])[iEvent]= CurrentEvents[iEvent].hstx;
 ((double*)EventFieldPointer[7])[iEvent]= CurrentEvents[iEvent].hsty;
 ((double*)EventFieldPointer[8])[iEvent]= CurrentEvents[iEvent].gstx;
 ((double*)EventFieldPointer[9])[iEvent]= CurrentEvents[iEvent].gsty;
 ((double*)EventFieldPointer[10])[iEvent]= CurrentEvents[iEvent].sta;
 ((double*)EventFieldPointer[11])[iEvent]= CurrentEvents[iEvent].henx;
 ((double*)EventFieldPointer[12])[iEvent]= CurrentEvents[iEvent].heny;
 ((double*)EventFieldPointer[13])[iEvent]= CurrentEvents[iEvent].genx;
 ((double*)EventFieldPointer[14])[iEvent]= CurrentEvents[iEvent].geny;
 ((double*)EventFieldPointer[15])[iEvent]= CurrentEvents[iEvent].ena;
 ((double*)EventFieldPointer[16])[iEvent]= CurrentEvents[iEvent].havx;
 ((double*)EventFieldPointer[17])[iEvent]= CurrentEvents[iEvent].havy;
 ((double*)EventFieldPointer[18])[iEvent]= CurrentEvents[iEvent].gavx;
 ((double*)EventFieldPointer[19])[iEvent]= CurrentEvents[iEvent].gavy;
 ((double*)EventFieldPointer[20])[iEvent]= CurrentEvents[iEvent].ava;
 ((double*)EventFieldPointer[21])[iEvent]= CurrentEvents[iEvent].avel;
 ((double*)EventFieldPointer[22])[iEvent]= CurrentEvents[iEvent].pvel;
 ((double*)EventFieldPointer[23])[iEvent]= CurrentEvents[iEvent].svel;
 ((double*)EventFieldPointer[24])[iEvent]= CurrentEvents[iEvent].evel;
 ((double*)EventFieldPointer[25])[iEvent]= CurrentEvents[iEvent].supd_x;
 ((double*)EventFieldPointer[26])[iEvent]= CurrentEvents[iEvent].eupd_x;
 ((double*)EventFieldPointer[27])[iEvent]= CurrentEvents[iEvent].supd_y;
 ((double*)EventFieldPointer[28])[iEvent]= CurrentEvents[iEvent].eupd_y;
 ((UINT16*)EventFieldPointer[29])[iEvent]= CurrentEvents[iEvent].status;
 ((UINT16*)EventFieldPointer[30])[iEvent]= CurrentEvents[iEvent].flags;
 ((UINT16*)EventFieldPointer[31])[iEvent]= CurrentEvents[iEvent].input;
 ((UINT16*)EventFieldPointer[32])[iEvent]= CurrentEvents[iEvent].buttons;
 ((UINT16*)EventFieldPointer[33])[iEvent]= CurrentEvents[iEvent].parsedby;
 
 // copying the string
		 mxArray* ConvertedString= mxCreateString(CurrentEvents[iEvent].Message.c_str());
		 mxSetCell(StringFieldMexPointer, iEvent, ConvertedString);
	  }   
  
  return mexEvent;
}

void CEDFFile::setMexRealFieldByNumber(mxArray *pm, mwIndex index, int fieldnumber, double Value)
{
  mxArray* RealFieldValue= mxCreateDoubleMatrix(1,1,mxREAL);
  *mxGetPr(RealFieldValue) = Value;
  mxSetFieldByNumber(pm,index,fieldnumber,RealFieldValue);
}

mxArray* CEDFFile::ExportPreamble()
{
	return mxCreateString(Preamble.c_str());
}

// -------------------- CEDFEvent
CEDFEvent::CEDFEvent(FEVENT Original)
{
	time= Original.time;
  type= Original.type;
  read= Original.read;
  eye= Original.eye;
  sttime= Original.sttime;
	entime= Original.entime;
  hstx= Original.hstx;
  hsty= Original.hsty;
  gstx= Original.gstx;
  gsty= Original.gsty;
  sta= Original.sta;
  henx= Original.henx;
  heny= Original.heny;
  genx= Original.genx;
  geny= Original.geny;
  ena= Original.ena;
  havx= Original.havx;
  havy= Original.havy;
  gavx= Original.gavx;
  gavy= Original.gavy;
  ava= Original.ava;
  avel= Original.avel;
  pvel= Original.pvel;
  svel= Original.svel;
  evel= Original.evel;
  supd_x= Original.supd_x;
  eupd_x= Original.eupd_x;
  supd_y= Original.supd_y;
  eupd_y= Original.eupd_y;
  status= Original.status;
  flags= Original.flags;
  input= Original.input;
  buttons= Original.buttons;
  parsedby= Original.parsedby;

  char MessageString[1024];
	LSTRING* MessegePtrInt= ((LSTRING*)Original.message);
  if (MessegePtrInt==0 || MessegePtrInt==NULL) // || MessegePtrInt==50 || MessegePtrInt==  150) 
	{
    strcpy(MessageString, "");
	}
	else
	{
		strncpy(MessageString, &(MessegePtrInt->c), MessegePtrInt->len);
	}
	Message= MessageString;
}
