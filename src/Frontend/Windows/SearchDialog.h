#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QDate>
#include <QCheckBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QGroupBox>

#include "../../Backend/Enums/Genres.h"


struct AdvancedFilters
{
    bool enabled = false;           
    QString type;                   
    QString titleContains;          
    QString authorContains;         
    bool useDateFrom = false;       
    QDate dateFrom;                 
    bool useDateTo = false;         
    QDate dateTo;                   
    bool onlyAvailable = false;     
    
    
    int bookGenre = -1;             
    int movieGenre = -1;            
    int musicGenre = -1;            
    int magazineGenre = -1;         
    int podcastGenre = -1;          
};


class SearchDialog : public QDialog
{
    Q_OBJECT
public:
    
    explicit SearchDialog(const AdvancedFilters& initial, QWidget* parent = nullptr);
    
    
    AdvancedFilters criteria() const { return current; }

private slots:
    
    void onTypeChanged(int idx);
    
    
    void onAccept();

private:
    
    void setupUI();
    void setupTypeSpecific();
    void populateFrom(const AdvancedFilters& initial);

    AdvancedFilters current;        

    
    QVBoxLayout* mainLayout;        
    QFormLayout* formLayout;        
    
    
    QComboBox* typeCombo;           
    QLineEdit* titleEdit;           
    QLineEdit* authorEdit;          
    QCheckBox* fromCheck;           
    QDateEdit* fromDate;            
    QCheckBox* toCheck;             
    QDateEdit* toDate;              
    QCheckBox* availableCheck;      

    
    QGroupBox* typeGroup;           
    QStackedWidget* typeStack;      
    
    
    QWidget* bookPage;              
    QComboBox* bookGenreCombo;      
    QWidget* moviePage;             
    QComboBox* movieGenreCombo;     
    QWidget* songPage;              
    QComboBox* musicGenreCombo;     
    QWidget* magazinePage;          
    QComboBox* magazineGenreCombo;  
    QWidget* podcastPage;           
    QComboBox* podcastGenreCombo;   
};

#endif 


