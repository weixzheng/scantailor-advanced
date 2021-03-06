
#ifndef SCANTAILOR_IMAGESETTINGS_H
#define SCANTAILOR_IMAGESETTINGS_H


#include <imageproc/BinaryThreshold.h>
#include <unordered_map>
#include <foundation/ref_countable.h>
#include <QtXml/QDomDocument>
#include <QtCore/QMutex>
#include <memory>
#include "PageId.h"

class AbstractRelinker;

class ImageSettings : public ref_countable {
public:
    class PageParams {
    public:
        PageParams();

        explicit PageParams(const imageproc::BinaryThreshold& bwThreshold);

        explicit PageParams(const QDomElement& el);

        QDomElement toXml(QDomDocument& doc, const QString& name) const;

        const imageproc::BinaryThreshold& getBwThreshold() const;

        void setBwThreshold(const imageproc::BinaryThreshold& bwThreshold);

    private:
        imageproc::BinaryThreshold bwThreshold;
    };

    ImageSettings() = default;

    ~ImageSettings() override = default;

    void clear();

    void performRelinking(const AbstractRelinker& relinker);

    void setPageParams(const PageId& page_id, const PageParams& params);

    std::unique_ptr<PageParams> getPageParams(const PageId& page_id) const;

private:
    typedef std::unordered_map<PageId, PageParams> PerPageParams;

    mutable QMutex mutex;
    PerPageParams perPageParams;
};


#endif  // SCANTAILOR_IMAGESETTINGS_H
