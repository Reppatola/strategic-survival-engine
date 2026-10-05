# Контракт: EventBus

## Зарегистрированные события

| Событие            | Payload                  | Издатель         | Подписчики           |
|--------------------|--------------------------|------------------|----------------------|
| `MOVEMENT_INTENT`  | `MovementIntentPayload`  | InputSystem      | MovementSystem       |
| `NOISE_GENERATED`  | `NoiseGeneratedPayload`  | MovementSystem   | NoiseSystem          |
| `POSITION_UPDATED` | `PositionUpdatedPayload` | MovementSystem   | RenderSystem         |

## Правила

1. **Запрещено** публиковать событие без регистрации в этой таблице.
2. Payload **должен** быть структурой с фиксированными полями.
3. Изменение структуры Payload требует обновления всех подписчиков.