#include "HDMConfigWindow.h"
#include "ui_HDMConfigWindow.h"
#include "qfiledialog.h"
#include <QMessageBox>
#include <filesystem>
#include <fstream>
#include "xml.h"
HDMConfigWindow::HDMConfigWindow(QString path, QWidget *parent)
    : QWidget(parent),
    path(std::move(path)),
    ui(new Ui::HDMConfigWindow)
{
    ui->setupUi(this);
    check_boxes.push_back(ui->activateAllDatabaseCountries);
    check_boxes.push_back(ui->allowAIAssumeDebt);
    check_boxes.push_back(ui->allowHumanClientStates);
    check_boxes.push_back(ui->allowDefenderAttackAttackerTerritory);
    spin_boxes.push_back(ui->anarchy_chanceDueToStability);
    spin_boxes.push_back(ui->anarchy_expectedStabilityLowerLimit);
    spin_boxes.push_back(ui->anarchy_expectedStabilityUpperLimit);
    spin_boxes.push_back(ui->anarchy_stabilityLowerLimit);
    spin_boxes.push_back(ui->annexationRelationLossPercent);
    check_boxes.push_back(ui->autoCovertMissions);
    spin_boxes.push_back(ui->civilWar_rebelsId);
    spin_boxes.push_back(ui->civilWar_chance);
    spin_boxes.push_back(ui->civilWar_controlChance);
    spin_boxes.push_back(ui->civilWar_annexChance);
    double_spin_boxes.push_back(ui->combatRangeDegrees);
    check_boxes.push_back(ui->compatibleSaveFormat);
    check_boxes.push_back(ui->continueAfterEconomicFailure);
    check_boxes.push_back(ui->continueAfterElectionLoss);
    check_boxes.push_back(ui->countryNeedsRegions);
    spin_boxes.push_back(ui->dedicatedServerAutosavePeriod);
    check_boxes.push_back(ui->dedicatedServerAutosaveToJoshuaFolder);
    check_boxes.push_back(ui->disableNuclearOnOccupy);
    check_boxes.push_back(ui->disbandAMDSOnOccupy);
    spin_boxes.push_back(ui->globalTaxLimit);
    spin_boxes.push_back(ui->globalTaxSpecials_exportAll);
    spin_boxes.push_back(ui->globalTaxSpecials_importAll);
    spin_boxes.push_back(ui->globalTaxSpecials_meetDomestic);
    spin_boxes.push_back(ui->globalTaxSpecials_privatizeAll);
    spin_boxes.push_back(ui->gvtTypeProductionModifiers_com);
    spin_boxes.push_back(ui->gvtTypeProductionModifiers_mil);
    spin_boxes.push_back(ui->gvtTypeProductionModifiers_mon);
    spin_boxes.push_back(ui->gvtTypeProductionModifiers_mpd);
    spin_boxes.push_back(ui->gvtTypeProductionModifiers_spd);
    spin_boxes.push_back(ui->gvtTypeProductionModifiers_the);
    check_boxes.push_back(ui->increaseDeathRateForAgingPopulation);
    spin_boxes.push_back(ui->incomeTaxLimits_com);
    spin_boxes.push_back(ui->incomeTaxLimits_mil);
    spin_boxes.push_back(ui->incomeTaxLimits_mon);
    spin_boxes.push_back(ui->incomeTaxLimits_mpd);
    spin_boxes.push_back(ui->incomeTaxLimits_spd);
    spin_boxes.push_back(ui->incomeTaxLimits_the);
    check_boxes.push_back(ui->incomeTaxRateAffectsGrowth);
    check_boxes.push_back(ui->logBankruptcies);
    spin_boxes.push_back(ui->maximumCellsInForeignCountry);
    text_edits.push_back(ui->message);
    spin_boxes.push_back(ui->militaryUpkeepPercentages_inf_eli);
    spin_boxes.push_back(ui->militaryUpkeepPercentages_inf_rec);
    spin_boxes.push_back(ui->militaryUpkeepPercentages_inf_reg);
    spin_boxes.push_back(ui->militaryUpkeepPercentages_inf_vet);
    spin_boxes.push_back(ui->militaryUpkeepPercentages_nav_eli);
    spin_boxes.push_back(ui->militaryUpkeepPercentages_nav_rec);
    spin_boxes.push_back(ui->militaryUpkeepPercentages_nav_reg);
    spin_boxes.push_back(ui->militaryUpkeepPercentages_nav_vet);
    spin_boxes.push_back(ui->militaryUpkeepPercentages_air_eli);
    spin_boxes.push_back(ui->militaryUpkeepPercentages_air_rec);
    spin_boxes.push_back(ui->militaryUpkeepPercentages_air_reg);
    spin_boxes.push_back(ui->militaryUpkeepPercentages_air_vet);
    spin_boxes.push_back(ui->militaryUpkeepPercentages_nuc);
    check_boxes.push_back(ui->navalRuleEnabled);
    spin_boxes.push_back(ui->nuclearMissileRangePercentage);
    spin_boxes.push_back(ui->occupiedRegionPercentageForNuclear);
    spin_boxes.push_back(ui->productionLossOnAnnex);
    spin_boxes.push_back(ui->resourceTaxLimit);
    spin_boxes.push_back(ui->tributePercent);
    check_boxes.push_back(ui->useNewExportMechanics);
    check_boxes.push_back(ui->useNewResourceTaxFormula);
}

HDMConfigWindow::~HDMConfigWindow()
{
    delete ui;
}


void HDMConfigWindow::on_toolButton_clicked()
{
    path = QFileDialog::getOpenFileName();
}

void load_info(QSpinBox* box, XMLNode* root){
    auto paths = box->objectName().split('_');
    XMLNode* node = root;
    for (auto& path : paths){
        node = node->get_child(path.toStdWString());
    }
    box->setValue(std::stoi(node->get_value()));
}
void load_info(QDoubleSpinBox* box, XMLNode* root){
    auto paths = box->objectName().split('_');
    XMLNode* node = root;
    for (auto& path : paths){
        node = node->get_child(path.toStdWString());
    }
    box->setValue(std::stod(node->get_value()));
}
void load_info(QCheckBox* box, XMLNode* root){
    auto paths = box->objectName().split('_');
    XMLNode* node = root;
    for (auto& path : paths){
        node = node->get_child(path.toStdWString());
    }
    box->setTristate(std::stoi(node->get_value()));
}
void load_info(QTextEdit* box, XMLNode* root){
    auto paths = box->objectName().split('_');
    XMLNode* node = root;
    for (auto& path : paths){
        node = node->get_child(path.toStdWString());
    }
    box->setText(QString::fromStdWString(node->get_value()));
}


void HDMConfigWindow::on_pushButton_load_clicked()
{
    std::wstring wpath = path.toStdWString();
    if (wpath.empty()){
        QMessageBox message_box;
        message_box.critical(0, "Не возможно открыть файл", "Вы не ввели путь");
        message_box.setFixedSize(300, 200);
        return;
    }
    if (!std::filesystem::exists(wpath)){
        QMessageBox message_box;
        message_box.critical(0, "Не возможно открыть файл", "Файл не существует");
        message_box.setFixedSize(300, 200);
        return;
    }
    std::wifstream file(wpath);
    if (!file.is_open()){
        QMessageBox message_box;
        message_box.critical(0, "Не возможно открыть файл", "Недостаточно прав");
        message_box.setFixedSize(300, 200);
        return;
    }
    file.imbue(std::locale("ru_RU.UTF-8"));
    XML xml(file);
    auto node = xml.get_child(L"SP2-HDM");
    for (auto& i : check_boxes){
        load_info(i, node);
    }
    for (auto& i : spin_boxes){
        load_info(i, node);
    }
    for (auto& i : double_spin_boxes){
        load_info(i, node);
    }
    for (auto& i : text_edits){
        load_info(i, node);
    }

}

