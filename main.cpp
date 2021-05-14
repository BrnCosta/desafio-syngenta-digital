#include <iostream>
#include <fstream>

void PixelsVerdes(const char* path){
    
    std::ifstream image;
    image.open(path, std::ios::in | std::ios::binary);

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;

    unsigned char fileHeader[fileHeaderSize];
    image.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);

    unsigned char informationHeader[informationHeaderSize];
    image.read(reinterpret_cast<char*>(informationHeader), informationHeaderSize);
    
    int m_width = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
    int m_height = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);

    unsigned char pixel;
    int count = 0;

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            unsigned char color[1];
            image.read(reinterpret_cast<char*>(color), 1);

            pixel = static_cast<float>(color[0]);

            if(pixel == 0x33){
                count++;
            }
        }
    }

    std::cout << "\n";
    std::cout << " 1-   Número de pixels verdes: " << count << std::endl;

    image.close();
}

void HiddenMessage(const char* path){
    
    std::ifstream img;
    std::ofstream text;

    img.open(path, std::ios::in | std::ios::binary);
    text.open("./message.txt");

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;

    unsigned char fileHeader[fileHeaderSize];
    img.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);

    unsigned char informationHeader[informationHeaderSize];
    img.read(reinterpret_cast<char*>(informationHeader), informationHeaderSize);
    
    int m_width = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
    int m_height = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);

    unsigned char image[m_height][m_width];
    unsigned char message[m_height][m_width];

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            unsigned char color[1];
            img.read(reinterpret_cast<char*>(color), 1);

            image[y][x] = color[0];
        }
    }
    img.close();

    int columns = 0;
    for (int y = 0; y < m_height; y++)
    {
        columns = 0;
        for (int x = (m_width*0.2); x < m_width; x++)
        {
            message[y][columns] = image[y][x];
            columns++;
        }
        
        columns = m_width*0.8;
        for (int x = 0; x < (m_width*0.2); x++)
        {
            message[y][columns] = image[y][x];
            columns++;
        }
    }

    for (int y = (m_height*0.6); y >= (m_height*0.49); y--)
    {
        for (int x = (m_width*0.57); x < m_width*0.90; x++)
        {
            text << message[y][x] << " ";
        }
        text << "\n";
    }

    std::cout << " 2-   Foi criado um arquivo message.txt na raiz do projeto" << std::endl;
    std::cout << "\n";
    text.close();
}

int main(){
    std::cout << "\n";
    std::cout << "Desafio Syngenta:" << std::endl;

    //Faz a contagem de quantos pixels verdes possui na imagem
    PixelsVerdes("./desafio_pixel_syngenta_digital/Syngenta.bmp");

    //Transforma a mensagem na imagem em um arquivo .txt
    HiddenMessage("./desafio_pixel_syngenta_digital/Syngenta.bmp");
}