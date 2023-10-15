
SIN = ['sin(pi/3) = ', num2str(sinTaylor(pi/3)), ' with Taylor'];
disp(SIN)
SIN = ['sin(pi/3) = ', num2str(sin(pi/3)), ' with matlab function'];
disp(SIN)

COS = ['cos(pi/6) = ', num2str(cosTaylor(pi/6)), ' with Taylor'];
disp(COS)
COS = ['cos(pi/6) = ', num2str(cos(pi/6)), ' with matlab function'];
disp(COS)

disp(' ')

SIN = ['sin(10pi) = ', num2str(sinTaylor(10*pi)), ' with Taylor'];
disp(SIN)
SIN = ['sin(10pi) = ', num2str(sin(10*pi)), ' with matlab function'];
disp(SIN)

sinTaylor(pi/4)


% rezultatul este afectat de rotunjirea care se intampla datorita reprezentarii 
% numerelor cu cat k este mai mare, cu atat eroarea va fi mai mare
% o solutie este sa folosim un x in intervalul [0,2*pi], folosindu-ne de
% periodicitatea functiilor sin si cos
