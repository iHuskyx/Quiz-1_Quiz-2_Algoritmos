// Quiz 1 y 2 Análisis de Algoritmos - Grupo01 - Andrea María Li Hernández 2021028783
#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Noticia { //Clase abstracta
public:
    string titulo;
    string fecha;
    string reportero;

    virtual ~Noticia() {}
    virtual void getInfo() = 0; //Método que cada clase hija debe implementar
};

class NoticiaPaper : public Noticia {   // Hereda de Noticia
public:
    string ruta; // Agrega una ruta al archivo de la foto de la noticia

    NoticiaPaper(string ruta, string titulo, string fecha, string reportero) {
        this->ruta = ruta;
        this->titulo = titulo;
        this->fecha = fecha;
        this->reportero = reportero;
    }
    ~NoticiaPaper() {}

    void getInfo() {
        cout << "Titulo: " << titulo << endl;   //Información del padre
        cout << "Fecha: " << fecha << endl;
        cout << "Reportero: " << reportero << endl;
        cout << "Ruta de la foto: " << ruta << endl;   // Información adicional de esta clase
    }
};

class Media {
public:
    string archivoAdjunto;  //Puede ser ruta de la foto o url del audio/video
    vector<int> posicion;   // El orden que tendrá en la noticia con coordenadas (x,y)
    virtual ~Media() {}
    virtual string getTipo() = 0; //Puede ser "Foto","Video" o "Audio" dependiendo de la clase hija
};

class Foto : public Media {
public:
    string fotografo;
    string fecha;

    Foto(string fotografo, string fecha, string rutaFoto, int x, int y) {
        this->fotografo = fotografo;
        this->fecha = fecha;
        this->archivoAdjunto = rutaFoto;
        vector<int> posicion{x,y};
        this->posicion = posicion;
    }
    ~Foto() {}

    string getTipo() {
        return "Foto";
    }
};

class Video : public Media {
public:
    string creador;

    Video(string urlVideo, string creador, int x, int y) {
        this->archivoAdjunto = urlVideo;
        this->creador = creador;
        vector<int> posicion{x,y};
        this->posicion = posicion;
    }
    ~Video() {}

    string getTipo() {
        return "Video";
    }
};

class Audio : public Media {
public:
    string creador;

    Audio(string urlAudio, string creador, int x, int y) {
        this->archivoAdjunto = urlAudio;
        this->creador = creador;
        vector<int> posicion{x,y};
        this->posicion = posicion;
    }
    ~Audio() {}

    string getTipo() {
        return "Audio";
    }
};


class NoticiaDigital : public Noticia {
public:
    list<Media*> media; // Lista con diversos tipos de media

    NoticiaDigital(list<Media*> media, string titulo, string fecha, string reportero) {
        this->media = media;    // Información adicional de esta clase
        this->titulo = titulo;
        this->fecha = fecha;
        this->reportero = reportero;
    }
    ~NoticiaDigital() {}

    void getInfo() {
        cout << "Titulo: " << titulo << endl;
        cout << "Fecha: " << fecha << endl;
        cout << "Reportero: " << reportero << endl;
        cout << "Media: [" << endl;     // Imprimir los contenidos de la lista con media
        for (auto med : media) {
            cout << med->getTipo() << ": ";
            cout << med->archivoAdjunto << endl;
        }
        cout << "]" << endl;
    }
};

class NoticiaRadio : public Noticia {
public:
    string urlAudioFile; // URL a un audio file

    NoticiaRadio(string url, string titulo, string fecha, string reportero) {
        this->urlAudioFile = url;
        this->titulo = titulo;
        this->fecha = fecha;
        this->reportero = reportero;
    }
    ~NoticiaRadio() {}

    void getInfo() {
        cout << "Titulo: " << titulo << endl;
        cout << "Fecha: " << fecha << endl;
        cout << "Reportero: " << reportero << endl;
        cout << "URL del audio file: " << urlAudioFile << endl; // Imprimir información adicional de esta clase
    }
};


int main()
{
    string titulo, fecha, reportero;
    titulo = "Los perros y gatos protegen a sus tutores de la perdida de memoria";
    fecha = "28 de Febrero de 2022";
    reportero = "Pedro Pascal";
    Noticia *noticiaPaper = new NoticiaPaper("C:/Users/usuario/Pictures/Noticia/Animales/Cat&Dog.jpg",
                                             titulo,fecha,reportero);

    // Crear media para la noticia digital
    Media *video = new Video("https://youtu.be/_goxZ5Bn_18", "Woof Dog", 0, 0);
    Media *foto = new Foto("Ksenia Raykova", "9 de marzo de 2020", "C:/Users/usuario/Pictures/Noticia/Animales/Cat&DogCute.jpg", 8, 0);
    Media *audio = new Audio("https://audioNoticia.com/noticiamascota", "Alexa Corrales", 10, 0);
    list<Media*> media = {video,foto,audio};
    Noticia *noticiaDigital = new NoticiaDigital(media, titulo,fecha,reportero);

    Noticia *noticiaRadio = new NoticiaRadio("https://audioNoticia.com/noticia",titulo,fecha,reportero);

    vector<Noticia*> noticias;  // Vector con una instancia de cada clase hija
    noticias.push_back(noticiaPaper);
    noticias.push_back(noticiaDigital);
    noticias.push_back(noticiaRadio);

    for (int i = 0; i < noticias.size(); i++) { // Invocar el método getInfo() para cada clase hija
        noticias[i]->getInfo();
        cout << endl;
    }

    cout << "Fin del programa. " << endl;

    // Eliminar los punteros de memoria dinámica
    for (int j = 0; j < noticias.size(); j++) {
        delete noticias[j];
    }
    delete foto;
    delete video;
    delete audio;
    delete noticiaPaper;
    delete noticiaDigital;
    delete noticiaRadio;
    return 0;
}
