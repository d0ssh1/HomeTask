Прикладная область этой системы – управление гостиничным бизнесом. Система позволяет эффективно управлять гостиничными услугами, такими как бронирование номеров, предоставление питания, уборка номеров и взаимодействие с клиентами.


Описание сущностей:

Human:
Основной абстрактный класс, представляющий человека.
Атрибуты: имя.

Client (Клиент):
Подкласс Human.
Функционал: бронирование номера, отмена бронирования.
Атрибуты: ID клиента.

Receptionist (Портье):
Подкласс Human.
Функционал: получение данных о клиенте, создание заказа, отмена заказа.
Атрибуты: номер портье.

Cleaner (Клинер):
Подкласс Human.
Функционал: уборка номера.
Атрибуты: номер комнаты для уборки.

Nutrition (Питание):
Предоставление информации о питании.
Атрибуты: тип питания, элементы меню, цена.
Функционал: изменение меню.

Order (Заказ):
Функционал: добавление услуги, расчет общей стоимости.
Атрибуты: ID заказа, ID клиента, номер комнаты, услуги, общая стоимость.

Room (Комната):
Функционал: бронирование комнаты, освобождение комнаты, изменение статуса комнаты.
Атрибуты: тип комнаты, цена, статус.

Company (Компания):
Функционал: найм сотрудника, увольнение сотрудника.
Атрибуты: название компании, список сотрудников.
