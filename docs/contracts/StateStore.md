# Контракт: StateStore

| Переменная        | Тип     | Издатель (запись) | Читатели              |
|-------------------|---------|--------------------|-----------------------|
| `AlertLevel`      | float   | AlertSystem        | ZombieAISystem        |
| `GlobalNoiseLevel`| float   | NoiseSystem        | ZombieAISystem        |
| `LastKnownPosition`| Vec3   | PerceptionSystem   | ZombieAISystem        |

## Правило

Ни одна система, кроме указанной в столбце «Издатель», **не имеет права** записывать в переменную.