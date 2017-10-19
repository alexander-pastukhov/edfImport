function [Trials]= edfCheckFixationStability(Trials, Fixation, ValidRadius)
%%  edfImport library v1.0 
%  Alexander Pastukhov 
%  kobi.nat.uni-magdeburg.de/edfImport
%  email: pastukhov.alexander@gmail.com
%  
%  edfCheckFixationStability
%  Verifies that all fixations happen within a safe radius around the fixation.
%
%  Syntax:
%    Trials= edfCheckFixationStability(Trials, Fixation, ValidRadius)
%
%  Description
%    Checks fixations for each trial to verify that they are within a safe radius away from the fixation. Fixation is a 2 element vector for the fixation position on the screen in pixels: [x, y]. ValidRadius - maximum tolerable deviation from fixation in degress of visual angle. Each trial is appended with a new Valid field, which is 1 if trial is valid and 0, if some fixations fell outside of the safe radius.

%% marking bad trials (with blinks and fixations outside of the safe radius) 
for iT= 1:length(Trials),
  %% creating a flag
  Trials(iT).StableFixation= 1;
  
  %% checking for fixations outside of the safe radius
  DistanceToCenter= hypot((Trials(iT).Fixations.gavx-Fixation(1))./Trials(iT).Fixations.PixInDegX, ...
                          (Trials(iT).Fixations.gavy-Fixation(2))./Trials(iT).Fixations.PixInDegY);
  iOutside= find(DistanceToCenter>ValidRadius);
  if (~isempty(iOutside))
    %% too bad - someone moved his/her eyes to much
    Trials(iT).StableFixation= 0;
  else
    Trials(iT).StableFixation= 1;
  end;
end;
