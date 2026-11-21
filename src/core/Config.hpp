#pragma once

// Convención de coordenadas: x de 0 a 400 (izquierda a derecha), y de 0 a 560 (arriba hacia abajo).
// La gravedad es positiva porque y crece hacia abajo, igual que en SFML.

namespace cfg
{
    // ---------------- Tiempo ----------------
    inline constexpr int tickRate = 60;                          // ticks/s; paso fijo de simulación, independiente de los FPS
    inline constexpr float tickDT = 1.0f/tickRate;               // s (0.01667); duración de un tick, derivada de tickRate
    inline constexpr int subSteps = 8;                           // subpasos/tick; más subpasos = pilas más estables y menos túneles
    inline constexpr float subStepDT = tickDT/subSteps;          // s (0.00208); paso de integración de Verlet
    inline constexpr int maxTicksPerFrame = 5;                   // ticks; tope por frame para evitar la espiral de recuperación tras un frame lento

    // ---------------- Tablero (unidades del mundo) ----------------
    inline constexpr float boxWidth = 400.f;                    // unidades; ancho interior de la caja
    inline constexpr float boxHeight = 560.f;                   // unidades; alto interior de la caja
    inline constexpr float leftWall = 0.f;                       // unidades (x); borde interior de la pared izquierda
    inline constexpr float rightWall = leftWall + boxWidth;      // unidades (x); derivada para que no quede desalineada si cambia el ancho
    inline constexpr float floorY = boxHeight;                   // unidades (y); el suelo es el borde inferior de la caja
    inline constexpr float dangerLineY = 80.f;                 // unidades (y); si una fruta la supera durante gameOverDelay, se pierde
    inline constexpr float dropY = 30.f;                         // unidades (y); altura donde aparece la fruta soltada, por encima de la línea de peligro

    // ---------------- Física ----------------
    inline constexpr float gravity = 1500.f;                    // unidades/s²; positiva porque y crece hacia abajo; ajustar a ojo
    inline constexpr float dampingPerSubStep = 0.995f;             // factor/subpaso; quita energía para que las frutas se detengan; muy bajo parece miel
    inline constexpr float maxDisplacementPerSubStep = 6.f;      // unidades/subpaso; la mitad del radio más pequeño (13), evita que atraviesen otras frutas
    inline constexpr float collisionCorrection = 0.6f;             // factor (0.5-0.8); corrige solo parte del solapamiento por subpaso para evitar temblores
    inline constexpr float floorFriction = 0.9f;                 // factor; desplazamiento horizontal conservado al tocar el suelo, evita que resbalen para siempre
    inline constexpr int mergeGrowTicks = 6;                       // ticks; la fruta nueva crece hasta su radio en este tiempo, evita explosiones al fusionar

    // ---------------- Reglas ----------------
    inline constexpr float cursorSpeed = 400.0f/tickRate;    // unidades/tick (6.67 = 400 unidades/s); la IA no puede superar esta velocidad
    inline constexpr int dropCooldown = tickRate/2;              // ticks (30 = 0.5 s); tiempo mínimo entre dos caídas
    inline constexpr int minFruitAgeForGameOver = 1 * tickRate; // ticks (60 = 1 s); edad mínima para contar en el fin de partida, da margen a la fruta recién soltada
    inline constexpr int gameOverDelay = 2*tickRate;            // ticks (120 = 2 s); tiempo seguido sobre la línea de peligro para perder
    inline constexpr int spawnableTiers = 5;                     // tiers; solo aparecen los tiers 0-4 (cereza a naranja)
    inline constexpr float settleEpsilon = 0.05f;                // unidades/tick; desplazamiento máximo para considerar el tablero quieto (isSettled)
    inline constexpr int settleTicks = 5;                        // ticks; ticks seguidos bajo settleEpsilon para que isSettled devuelva true

    // ---------------- Ventana y vistas ----------------
    inline constexpr float screenWidth = 1280.f;               // px; ancho de la ventana, cada jugador usa la mitad (640)
    inline constexpr float screenHeight = 720.f;               // px; alto de la ventana
    inline constexpr int frameLimit = 60;                       // FPS; límite de dibujo, no afecta la simulación
    inline constexpr float boxViewWidth = 560.f;                // unidades; misma proporción que media ventana (640/720 = 0.889), deja 80 a cada lado
    inline constexpr float boxViewHeight = 630.f;               // unidades; deja 70 unidades extra para la siguiente fruta y el puntaje


}