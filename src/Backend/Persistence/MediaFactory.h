#pragma once

#include <memory>
#include <string>

class Media;
class QJsonObject;
class QXmlStreamAttributes;
class QString;
class Date;

namespace MediaFactory {
    struct Common {
        std::string title;
        std::string author;
        Date* releaseDatePtr; 
        unsigned id{};
        unsigned sizeKb{};
        bool available{};
        std::string imagePath;
    };

    std::unique_ptr<Media> fromJson(const QString& type, const Common& c, const QJsonObject& o);
    std::unique_ptr<Media> fromXml(const QString& type, const Common& c, const QXmlStreamAttributes& attrs);
}
