%%Ejercicio 11 QUantizer

% 1. Calcular el valor máximo de los coeficientes
Coef_max = max(abs(Num_7));
disp('Valor máximo del coeficiente:');
disp(Coef_max);

% Determinar número de bits enteros necesarios (incluye bit de signo)
num_bits_enteros = ceil(log2(Coef_max + 1));
disp('Número de bits enteros necesarios:');
disp(num_bits_enteros);

% 2. Configuración de cuantizadores con diferentes números de bits fraccionarios
q1 = quantizer('fixed', 'round', 'saturate', [5 4]); % 5 bits totales, 4 fraccionarios
%q2 = quantizer('fixed', 'round', 'saturate', [6 5]);
% q3 = quantizer('fixed', 'round', 'saturate', [7 6]);
% q4 = quantizer('fixed', 'round', 'saturate', [8 7]);
% q5 = quantizer('fixed', 'round', 'saturate', [9 8]);
q6 = quantizer('fixed', 'round', 'saturate', [12 11]);
q7 = quantizer('fixed', 'round', 'saturate', [13 12]);




% Cuantificar los coeficientes
Coef_q1 = quantize(q1, Num_7);
% Coef_q2 = quantize(q2, Num_7);
%Coef_q3 = quantize(q3, Num_7);
%Coef_q4 = quantize(q4, Num_7);
%Coef_q5 = quantize(q5, Num_7);
Coef_q6 = quantize(q6, Num_7);
Coef_q7 = quantize(q7, Num_7);
Coef_q8 = quantize(q8, Num_7);

% 3. Calcular las respuestas en frecuencia
[HNum, w] = freqz(Num_7, 1); % Respuesta original
[Hq1, w] = freqz(Coef_q1, 1);
% [Hq2, w] = freqz(Coef_q2, 1);
% [Hq3, w] = freqz(Coef_q3, 1);
% [Hq4, w] = freqz(Coef_q4, 1);
% [Hq5, w] = freqz(Coef_q5, 1);
[Hq6, w] = freqz(Coef_q6, 1);
[Hq7, w] = freqz(Coef_q7, 1);



% 4. Dibujar las respuestas en frecuencia (Módulo)
figure;
plot(w / (2 * pi) * 8000, 20 * log10(abs([HNum, Hq1, Hq5, Hq6, Hq7])));
legend('Precisión infinita', '5 bits', '9 bits', '12 bits', '13 bits');
xlabel('Frecuencia (Hz)');
ylabel('Módulo (dB)');
title('Respuesta en frecuencia (Módulo)');

% 5. Dibujar las respuestas en frecuencia (Fase)
figure;
plot(w / (2 * pi) * 8000, unwrap(angle([HNum, Hq1, Hq2, Hq6, Hq7])));
legend('Precisión infinita', '5 bits', '9 bits', '12 bits', '13 bits');
xlabel('Frecuencia (Hz)');
ylabel('Fase (rad)');
title('Respuesta en frecuencia (Fase)');

% 6. Conclusión
disp('Analiza las gráficas para determinar el mínimo número de bits fraccionarios que cumplen las especificaciones.');
