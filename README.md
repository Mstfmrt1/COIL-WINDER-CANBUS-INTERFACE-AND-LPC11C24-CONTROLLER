# COIL-WINDER-CANBUS-INTERFACE-AND-LPC11C24-CONTROLLER
Bobin Sarma Makinesi

Arayüzden alınan hız ve tur sayısı değerine göre LPC11C24 mikrokontrolcüye CanBus aracılığıyla mesajları iletilir.
MCU aldığı mesajları işleyerek DC motora gelen  PWM değerinde döndürmeye başlar, kullanılan Inductive Sensör prototip tasarımda her dönüşünde bir sayarak arayüze anlık tur bilgilerini yollar
ve istenilen tur sayısına ulaştığında motoru durdurur. İşlem anında motorun durması istenirse stop butonu ile durdurulabilir.
Bu sisteme prototip bir sarım makinesi tasarımı gerçekleştirildi ve çalıştırıldı.


<img width="461" alt="control" src="https://user-images.githubusercontent.com/104312094/224980062-47decf7c-102f-4303-9892-5fa0665ed352.PNG">
