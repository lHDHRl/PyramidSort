import random
import string

def generate_student_record(id):
    """
    Генерирует одну запись студента.
    Возвращает кортеж: (фамилия, имя, отчество, номер группы, id)
    """
    surname = ''.join(random.choices(string.ascii_uppercase, k=5))
    name = ''.join(random.choices(string.ascii_uppercase, k=6))
    middlename = ''.join(random.choices(string.ascii_uppercase, k=7))
    group_number = random.randint(1000, 9999)
    return (surname, name, middlename, group_number, id)

def record_to_string(record):
    """
    Преобразует запись-студента в строку для записи в файл.
    Формат: "фамилия имя отчество номер_группы id\n"
    """
    surname, name, middlename, group, id = record
    return f"{surname} {name} {middlename} {group} {id}\n"

def generate_students(n):
    """
    Генерирует список из n записей студентов.
    """
    return [generate_student_record(i) for i in range(1, n + 1)]

def save_students(filename, students):
    """
    Сохраняет список записей студентов в файл.
    """
    with open(filename, 'w') as f:
        for record in students:
            f.write(record_to_string(record))

if __name__ == '__main__':
    n = 10000  # Можно изменить количество записей

    # 1. Случайный порядок
    students_random = generate_students(n)
    save_students("students_random.txt", students_random)
    print("Файл 'students_random.txt' с записями студентов в случайном порядке сгенерирован.")

    # 2. Уже отсортированный массив.
    # Сортируем по номеру группы (возрастание), а при равенстве – по фамилии, имени, отчеству (алфавитный порядок)
    students_sorted = sorted(students_random, key=lambda r: (r[3], r[0], r[1], r[2]))
    save_students("students_sorted.txt", students_sorted)
    print("Файл 'students_sorted.txt' с отсортированным массивом студентов сгенерирован.")

    # 3. Элементы расположены в обратном порядке.
    students_reverse = list(reversed(students_sorted))
    save_students("students_reverse.txt", students_reverse)
    print("Файл 'students_reverse.txt' с массивом студентов, отсортированных в обратном порядке, сгенерирован.")
