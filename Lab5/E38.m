

% Diseño de filtros
filtro_pb = fir1(46, 0.6, 'low'); % Filtro paso bajo
filtro_pa = fir1(46, 0.6, 'high'); % Filtro paso alto

% Escalado a valores enteros
max_val = 2^15 - 1;
filtro_pb_escalado = round(filtro_pb / max(abs(filtro_pb)) * max_val);
filtro_pa_escalado = round(filtro_pa / max(abs(filtro_pa)) * max_val);

% Impresión de los coeficientes
fprintf('Coeficientes del filtro paso bajo:\n');
fprintf('%d\n', filtro_pb_escalado);
fprintf('Coeficientes del filtro paso alto:\n');
fprintf('%d\n', filtro_pa_escalado);

% Calcular el factor de corrección de los filtros
desplaza_pb = ceil(log2(sum(abs(filtro_pb_escalado))));
fprintf(1, 'Desplazamiento registro pasobajo = %d\n', desplaza_pb);
desplaza_pa = ceil(log2(sum(abs(filtro_pa_escalado))));
fprintf(1, 'Desplazamiento registro pasoalto = %d\n\n', desplaza_pa);

% FFT para respuesta en frecuencia
N= 1024; % Número de puntos para la FFT
H_pb_fft = fft(filtro_pb_escalado, N);
H_pa_fft = fft(filtro_pa_escalado, N);

% Frecuencias correspondientes (normalizadas)
frecuencia = (0:N-1) / N; % Frecuencia normalizada [0, 1)

% Gráficas
figure;
subplot(2,1,1);
plot(frecuencia(1:N/2), 20*log10(abs(H_pb_fft(1:N/2))));
title('Respuesta en frecuencia - Filtro Paso Bajo (FFT)');
xlabel('Frecuencia normalizada');
ylabel('Magnitud (dB)');
grid on;

subplot(2,1,2);
plot(frecuencia(1:N/2), 20*log10(abs(H_pa_fft(1:N/2))));
title('Respuesta en frecuencia - Filtro Paso Alto (FFT)');
xlabel('Frecuencia normalizada');
ylabel('Magnitud (dB)');
grid on;
