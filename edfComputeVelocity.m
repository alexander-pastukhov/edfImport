function [Trials]= edfComputeVelocity(Trials, VelocityBraketMS)
%%  edfImport library v1.0 
%  Alexander Pastukhov 
%  kobi.nat.uni-magdeburg.de/edfImport
%  email: pastukhov.alexander@gmail.com
%    
%  edfComputeVelocity
%  Computes eye velocity based on raw samples
%
%  Syntax:
%    Trials= edfComputeVelocity(Trials,VelocityBraketMS)
%    Trials= edfComputeVelocity(Trials)
%
%  Description:
%    Computes eye velocities using raw eye positions. This requires that
%    Samples field exists (i.e. samples were imported) and the following
%    fields are present: time, gx, gy. Refresh rate of the camera for recording
%    is taken from Trials().Header.rec.sample_rate field.    
%
%    Additional options and their default values (used if the option is
%    omitted), for more details consult Engbert \& Kliegl (2003). 
%    * VelocityBraketMS: time span around current sample with which to
%      compute the velocity in milliseconds. Default: 20 ms.

%% using default values, if some parameters are empty or undefined
if (~exist('VelocityBraketMS', 'var') || isempty(VelocityBraketMS))
%   disp('No value for velocity braket to compute velocity. Using default value: 20 ms.');
  VelocityBraketMS= 20;
end;

%% doing trial-by-trial analysis
for iTrial= 1:length(Trials),
%     iTrial
  %% getting data
  DeltaT= 1000/Trials(iTrial).Header.rec.sample_rate;
 
  %% checking that data is where
  if (~isfield(Trials(iTrial), 'Samples'))
    throw(MException('edfMATLAB:edfExtractMicrosaccades:NoSamplesField', 'No Samples field in for trial %d', iTrial));    
  end;
  if (~isfield(Trials(iTrial).Samples, 'time'))
    throw(MException('edfMATLAB:edfExtractMicrosaccades:NoTimeField', 'No "time" field in Samples for the trial %d', iTrial));    
  end;
  if (~isfield(Trials(iTrial).Samples, 'gx'))
    throw(MException('edfMATLAB:edfExtractMicrosaccades:NoGXField', 'No "gx" field in Samples for the trial %d', iTrial));    
  end;
  if (~isfield(Trials(iTrial).Samples, 'gy'))
    throw(MException('edfMATLAB:edfExtractMicrosaccades:NoGYField', 'No "gy" field in Samples for the trial %d', iTrial));    
  end;

  %% computing velocities
  BracketInSamples= ceil((VelocityBraketMS/DeltaT-1)/2);
  CommonFactor= 2*sum(1:BracketInSamples)*DeltaT/1000;
  Trials(iTrial).Samples.velx= zeros(size(Trials(iTrial).Samples.gx));
  Trials(iTrial).Samples.vely= zeros(size(Trials(iTrial).Samples.gx));
  for iT= BracketInSamples+1:size(Trials(iTrial).Samples.gx, 2)-BracketInSamples,
    Trials(iTrial).Samples.velx(:, iT)= sum(-Trials(iTrial).Samples.gx(:, iT-[1:BracketInSamples])+Trials(iTrial).Samples.gx(:, iT+[1:BracketInSamples]), 2)./CommonFactor;
    Trials(iTrial).Samples.vely(:, iT)= sum(-Trials(iTrial).Samples.gy(:, iT-[1:BracketInSamples])+Trials(iTrial).Samples.gy(:, iT+[1:BracketInSamples]), 2)./CommonFactor;
  end;
end;
