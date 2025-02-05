% %obtiene la respuesta en frecuencia
% [Hham,w]=freqz(Num_Hann,1);
% %dibuja módulo y fase de la respuesta en frecuencia
% figure
% plot(w/2/pi*8000,20*log10(abs(Hham )))
% xlabel('Frecuencia (Hz)')
% ylabel('Módulo (dB)')
% grid
% figure
% plot(w/2/pi*8000,unwrap(angle(Hham)))
% xlabel('Frecuencia (Hz)')
% ylabel('Fase (rad)')
% grid

% %EJERCICIO 14, obtención de 0's y polos
% %el elíptico es el de menor orden (4)
% figure;
% [z,p,k]=zplane(Num_Elliptic,Den_Elliptic);
% 
% grid on;
% title('Diagrama de polos y ceros de filtro Elliptical')


%EJERCICIO 15
%CUANTIFICACIÓN DE 6 BITS DEL ELLIPTICAL
% 
% Coef_max_Num=max(abs(Num_Elliptic)); %sale 2.32
% Coef_max_Den=max(abs(Den_Elliptic)); %sale 2.14
% q6 = quantizer('fixed', 'round', 'saturate', [6 3]);
% Num_q6=quantize(q6,Num_Elliptic);
% Den_q6=quantize(q6,Den_Elliptic);
% %[Hq6,w]=freqz(Num_q6,1);
% 
% figure;
% [z6,p6,k6]=zplane(Num_q6,Den_q6);
% grid on;
% title('Diagrama de polos y ceros de filtro Elliptical cuantificado con 6b')

%EJERCICIO 18
Coef_max_SOS = max(abs(SOS(:))); %sale 1.96

q6 = quantizer('fixed', 'round', 'saturate', [10 8]);

SOS_q6 = quantize(q6, SOS);

% % Diagrama de Polos y Ceros
% figure;
% 
% subplot(1, 2, 1);
% zplane(SOS(:, 1:3), SOS(:, 4:6)); % Polos y ceros del filtro original
% title('Polos y ceros: Original');
% 
% subplot(1, 2, 2);
% zplane(SOS_q6(:, 1:3), SOS_q6(:, 4:6)); % Polos y ceros del filtro cuantificado (6 bits)
% title('Polos y ceros: Cuantificado (6 bits)');

