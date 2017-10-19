function [FieldFlags]= edfSelectSampleFields(FieldNames)
%%  edfImport library v1.0 
%  Alexander Pastukhov 
%  kobi.nat.uni-magdeburg.de/edfImport
%  email: pastukhov.alexander@gmail.com
%
%  Converts list of space-separated names of FSAMPLE structure
%  fields into a boolean array of flags, later passed to
%  edfMexImport function. Used by edfImport.  


%% Names of fields from FSAMPLE structure
SampleFields= {'time', 'flags', 'px', 'py', 'hx', 'hy', 'pa', 'gx', 'gy', 'rx', 'ry', 'status', 'input', 'buttons', 'htype', 'hdata', 'errors', 'gxvel', 'gyvel', 'hxvel', 'hyvel', 'rxvel', 'ryvel', 'fgxvel', 'fgyvel', 'fhxvel', 'fhyvel', 'frxvel', 'fryvel'};
FieldFlags= zeros(1, 29);

%% getting read of extra spaces
FieldNames= strtrim(FieldNames);

%% locating all words in-between spaces
[iStart, iEnd]= regexp(FieldNames, '[ ]*');
iWordStart= [1 iEnd+1];
iWordEnd= [iStart-1 length(FieldNames)];

%% looping through words in-between spaces
for iS= 1:length(iWordStart),
  CurrentName= FieldNames(iWordStart(iS):iWordEnd(iS));
  iField= find(strcmp(SampleFields, CurrentName));
  if (~isempty(iField))
    FieldFlags(iField)= 1;
  elseif (length(CurrentName)>0)
     throw(MException('edfMATLAB:edfSelectSampleFields:BadFieldName', 'Unknown FSAMPLE structure field "%s"', CurrentName));    
  end;
end;