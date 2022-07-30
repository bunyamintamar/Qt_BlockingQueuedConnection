# Qt::BlockingQueuedConnection Kullanımı

Bu yazıda Qt framework’ünün **signal-slot** yapısının uygulama aşamalarından olan **Qt::QueedConnection** yapısından ve **Qt::BlockingQueuedConnection** ile arasındaki farktan bahsedeceğim.

Öncelikle **signal-slot nedir** sorusuna hızlıca bir cevap vereyim. Basitçe ***objeler arası iletişim yöntemidir*** diyebiliriz. Bir obje diğer objeye bir sinyal fırlatır ve bu sinyalin gelmesiyle diğer objenin bir metodu tetiklenmiş olur. Tetiklenen bu metoda da **slot** denir. Objeler arası dedim ama **aynı** objenin bir slotuna da sinyal bağlanabilir. Signal-slot yapısı Qt’ün temelini oluşturur ve Qt framework’ünün biz yazılımcılara sağladığı çok büyük bir nimettir.

Signal-slot yapısının kullanılabilmesi için ilgili objelerin **QObject** class’ından türemesi veya **Q_OBJECT** makrosunun bu class’ların **private bölgesine** eklenmesi gerekmedir.

*Signal-slot kavramı hakkında daha geniş bilgiye başka kaynaklardan ulaşılabilir. Asıl konumuzdan sapmamak için bu kadar ön bilgiyi yeterli görüyorum.*

Asıl konuya geçelim artık.

Signal-slot mekanizması **aynı thread içerisinde kullanılmak istenirse** sinyal yayıldığı anda slot metod çağrılır. Bir metodu normal bir şekilde çağırmaktan bir farkı yok gibi. Buna **Qt::DirectConnection** denir ve sinyale anlık bir tepki olarak slot metod çağrılmış olur. Signal-slot yapısının en basit hali ve çoğu kişinin Qt’ün signal-slot yapısını öğrendiğinde deneyimlediği ilk connection yapılarından biridir. Yeni bir proje tanımlayıp A ve B class’larımız arasında yaptığımız connection tipi budur.

**Main thread’imizden ayrı iki farklı thread daha olduğunu ve bu thread’ler arasında signal-slot yapısının kurulduğunu düşünelim.** İki thread arasında sinyal yayınlandığı anda slot metod **hemen çağrılmaz**. Bunun yerine sinyal **bir kuyruğa eklenir** ve sırası gelince bağlandığı slot metod çağrılır. **Anlık bir tepki yoktur** ve kuyruk mekanizması olduğu için bir **gecikme** vardır. Bu mekanizmaya **Qt::QueuedConnection** denir. Detaylı bilgiye Qt’ün [dokümanlarından](https://doc.qt.io/qt-6/qt.html#ConnectionType-enum) ulaşılabilir.

Diyelim ki elimizde **MainThread** ve **SecondThread** isimli iki adet thread’imiz var. **SecondThread** bir **sinyal** fıtlatsın ve **MainThread**’deki bir **slot** çalışsın. Bu iki thread’in şöyle ayrıntıları olsun.

1. **SecondThread**’den yayılan sinyal **100 ms**’de bir yayılsın ve **MainThread**’de bulunan bir slotu çalıştırsın.
2. Fakat, **MainThread**’de bulunan slot ise çalışmasını **200 ms**’de tamamlasın.

**Bu durumda şöyle bir problemimiz olacak:**

Sinyal 100 ms’de bir art arda gelse bile slot metodda yapılan iş uzun sürdüğü için kuyruktaki sinyallerin slotu tetiklemesi 200 ms’de bir gerçekleşmiş olacak. Hatta sinyaller kuyruğa alınıp işlendiği için senkronizasyonun bozulması yetmezmiş gibi sinyal göndermeyi kesseniz bile **kuyruk boşalana kadar slot tetiklenmeye devam edecek**. Bu, hiç de istenilen bir durum değil.

İşte burada imdadımıza **Qt::BlockingQueuedConnection** yapısı yetişir. Sinyal fırlatılınca kuyruğa alınır ve tetiklenmesi istenen slot tetiklenip işini tamamlayana kadar aynı sinyalin tetiklenmesi ve dolayısıyla kuyruğa alınması engellenmiş olur.


---

[Bünyamin TAMAR - Yazılım Geliştirme Uzmanı - ASİS CT | LinkedIn](https://www.linkedin.com/in/bunyamintamar/)