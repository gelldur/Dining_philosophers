//
// Created by Dawid Drozd aka Gelldur on 22/01/17.
//
#pragma once

#include <memory>

#include <QtWidgets/QWidget>

#include <controller/PhilosopherMindController.h>
#include <ui_philosopherView.h>

class PhilosopherController : public QWidget
{
Q_OBJECT
	using inherited = QWidget;
public:
	explicit PhilosopherController(const std::string& name, QWidget* parent = nullptr);
	virtual ~PhilosopherController();

public slots:
	/**
	 * Philosopher sends signall to kill. Called by button "kill"
	 */
	void onKill();

	/**
	 * When something changed in model this method will be called to update UI
	 */
	void onUpdateUI();

protected:
	virtual void showEvent(QShowEvent* event) override;

private:
	std::unique_ptr<Ui::PhilosopherView> _ui;
	PhilosopherMindController _thread;
};


