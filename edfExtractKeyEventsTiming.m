function [Trials]= edfExtractKeyEventsTiming(Trials)
%%  edfImport library v1.0
%  Alexander Pastukhov 
%  kobi.nat.uni-magdeburg.de/edfImport
%  email: pastukhov.alexander@gmail.com
%
%  edfExtractKeyEventsTiming
%  Extracts time of the events recorded with KEY_EVENT message.
%
%  Syntax:
%    Trials= edfExtractKeyEventsTiming(Trials)
%
%  Description:
%    This is a non-standard function used in our lab. In order to have precise timing of
%    experimental events in eye-tracker time units, I record them using
%    eyemsg_printf("KEY_EVENT SomeImportantEvent"). This way I know exactly
%    when it happened and later use this function to extract the timing.
%    Information is stored in the new field KeyEvents with each event name
%    being a new subfield and timing in eye tracker time units stored as a
%    value. For example "KEY_EVENT MaskOnset" becomes
%    Trials(iT).KeyEvents.MaskOnset= T; (there T is the time of the event).
%    Note, you can use event codes like "KEY_EVENT FrameOnset(1)" and
%    "KEY_EVENT FrameOnset(2)", in this case you will get a two element
%    vector KeyEvents.FrameOnset= [T1 T2];

for iTrial= 1:length(Trials),
  Trials(iTrial).KeyEvents= [];
  for iEvent= 1:length(Trials(iTrial).Events.message),
    if (regexp(Trials(iTrial).Events.message{iEvent}, '^KEY_EVENT'))
      CurrentExpression= strtrim(Trials(iTrial).Events.message{iEvent}(10:length(Trials(iTrial).Events.message{iEvent})));
      CurrentExpression= [CurrentExpression '= ' num2str(Trials(iTrial).Events.sttime(iEvent)) ';'];
      eval(sprintf('Trials(iTrial).KeyEvents.%s', CurrentExpression));
    end;
  end;
end;