function [Trials]= edfExtractVariables(Trials)
%%  edfImport library v1.0 
%  Alexander Pastukhov 
%  kobi.nat.uni-magdeburg.de/edfImport
%  email: pastukhov.alexander@gmail.com
%  
%  edfExtractVariables
%  Extracts variables and their values from TRIAL_VAR messages. Note
%  TRIAL_VAR_LABELS and TRIAL_VAR_DATA are currently not supported. 
%
%  Syntax:
%  	 Trials= edfExtractVariables(Trials)
%
%  Description:
%    Extracts variables and their values from TRIAL_VAR messages (in Events
%    structure) and stores them into a new field Variables with each
%    variable being a new subfield. During recording variables can be 
%    saved using either space-separated format 'TRIAL_VAR VarName VarValue'
%    or using a MATLAB-compatible syntax 'TRIAL_VAR VarName=VarValue'. In
%    the latter case you can use any MATLAB-legal expression for VarValue.      


for iT= 1:length(Trials),
  Trials(iT).Variables= [];

  iBadValue= 1;
  for iE= 1:length(Trials(iT).Events.type),
    if (regexp(Trials(iT).Events.message{iE}, 'TRIAL_VAR '))
      %% extracting name+value part
      CurrentExp= Trials(iT).Events.message{iE};
      CurrentExp(1:10)= [];
      CurrentExp= strtrim(CurrentExp);
      
      iAssign= regexp(CurrentExp, '=');
      try
        if (~isempty(iAssign))
          %% matlab format 'Name= Value'
            eval(sprintf('Trials(iT).Variables.%s;', CurrentExp));
        else
          %% DataViewer format 'Name Value'
          Space= regexp(CurrentExp, ' ');
          Space= Space(1);
          CurrentVar= strtrim(CurrentExp(1:Space-1));
          CurrentVal= strtrim(CurrentExp(Space:length(CurrentExp)));
          if (isempty(intersect(CurrentVal(1), ['a':'z' 'A':'Z'])))
            %% does not start with a letter, could be a numerical value or an array or a properly writtent string (with ')
            eval(sprintf('Trials(iT).Variables.%s= %s;', CurrentVar, CurrentVal));
          else
            %% starts with letters - string
            eval(sprintf('Trials(iT).Variables.%s= ''%s'';', CurrentVar, CurrentVal));
          end;
        end;
      catch ME
        %% something went wrong
        eval(sprintf('Trials(iT).BadValueVar%f= ''%s'';', iBadValue, CurrentExp));
        iBadValue= iBadValue+1;
      end;
    end;
  end;
end;

