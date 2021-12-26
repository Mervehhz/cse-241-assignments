oyunda her bir kısım ;

hamle alma, undo pre decrement, undo post decrement üçlüsünden oluşmakta.


eğer user vs computer modda kullanıcı hamle girerse undo yapmak istiyor musunuz diye sorar,
eger evet derseniz pre decrementte;
hamleyi geri alır ve computer hamleyi yapmadan kullanıcıdan yine hamle alır ve boarda koyar, sonra computer hamle yapar, oyun devam eder..
eğer evet derseniz post decrementte;
post decrement dediğimiz şey önce oyna sonra hamleyi geri al olduğu için siz post decrement seçeneğine yes dediğiniz an hemen boarddan silmez, oyun bir tur oynandıktan sonra
o hamleyi boarddan siler.


eğer user vs user modda oynuyorsanız;

ilk kullanıcı hamle girer ve pre incrementte undo yaparsa;
ikinci user hamle girmeden o an hamleyi geri alır  ve kullanıcıdan yeni hamle alır onu boarda koyar, sonra oyun adevam eder.

ilk kullanıcı hamle girer ve post incrementte undo yaparsa;
o hamle hala boardda kalır ve bir tur oynanıca siler. bir tur 2 kullanıcının da hamllerini kapsar ve ayrıca örneğin 'o' harfi undo post decrement yaparsa bundan sonraki hamle yine
'o' olur. çünkü hamlesini geri çekti, yendiden hamle girmesi lazım. sonra oyun devam eder.


undo ile ilgili son olarak;
multigamede oynarken eğer bir taraf kazandıysa o an hemen kazandınız demez turu tamamlamanı bekler yani bu durumda undo seçeneklerine no demeniz gerekir, no dedikten sonra oyun biter.


hocam size ayrı bir not olarak;

destructoru kullanmaya çalıştığımda multi game kısmında double free detected hatası alıyorum.
ayrıca kendim ayrı bir destructor yazdığımda (adı ~Hex olmayan) segmentation fault veriyor.
nasıl yapacağımı bilemedim ve ayrıca sınavla üst üste geldiği için özellikle uğraşamadım.
bu yüzden destructoru yazdım fakat yoruma aldım.

ayrıca bir tane warning veriyor hocam.
o parametreyi overload etmek için zorunlu olarak kullandım.