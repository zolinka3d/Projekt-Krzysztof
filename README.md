WTSĘP: Naszym zadaniem było zrobić program, który pobiera dane kątowe z pliku - outputPendulum01.
Funkcja pobierająca dane:
![1](https://user-images.githubusercontent.com/84075025/122977547-d4e07600-d395-11eb-91e7-8547b1cead3c.png)

Przedstawić te dane na wykresie w stworzonej przez nas aplikacji Win Api w języku programowania cpp. Pobrane dane kątowe są wyświetlane na wykresie oraz liczona jest wysokość na jakiej znajduje się wahadło w danym momencie.
Funkcja zamieniająca stopnie na radiany oraz funkcja licząca wysokość wahadła:
![2](https://user-images.githubusercontent.com/84075025/122977586-e033a180-d395-11eb-968f-3ad3f2d4c3cf.png)

Funkcja rysująca wykres:
![3](https://user-images.githubusercontent.com/84075025/122977633-ede92700-d395-11eb-86b0-84c9686fad65.png)
![4](https://user-images.githubusercontent.com/84075025/122977679-fb9eac80-d395-11eb-8ca3-2b35ca3332f1.png)

JAK KORZYTSAĆ Z PROGRAMU?
W konsli należy podać ile pierwszych wierszy danych chcemy pominąć. Po zaakceptowaniu ENTER'em wyświetli nam się okno z rysowanymi wykresami w czasie. Wykresy przedstawiają: kąt pitch, kąt roll i wysokość wahadła.
![5](https://user-images.githubusercontent.com/84075025/122977721-05c0ab00-d396-11eb-9d10-799d7adf1f8c.png)

W trakcie rysowania wykresu możemy na bierząco zmnieniać skalę x(czas) oraz y(amplituda) za pomocą przycisków "+" oraz "-" położonymi przy danej osi:
![6](https://user-images.githubusercontent.com/84075025/122977764-11ac6d00-d396-11eb-99b9-f8cbb1f1e8fa.png)

NAJWAŻNIEJSZE CZĘŚCI KODU:
Program pyta się ile wierszy chcemy usunąć, a następnie z wcześniej utworzonego wektora usuwa podaną ilość danych.
![8](https://user-images.githubusercontent.com/84075025/122977810-1bce6b80-d396-11eb-83f7-a90e01ec83fd.png)

Następnie tworzone jest okno z odpowiednim rozmieszczeniem przycisków.
![9](https://user-images.githubusercontent.com/84075025/122977835-24bf3d00-d396-11eb-94a4-28e2b9b5fba0.png)

Najważniejszą częścią kodu jest funkcja timera odpowiedzialna za rysowanie wykresu w czasie, anie natychmiastowo.
![10](https://user-images.githubusercontent.com/84075025/122977914-34d71c80-d396-11eb-852e-6a31cdb114aa.png)
