#include "ScenarioMapper.h"

#include <Domain/Scenario.h>

using namespace DataMappingLayer;


namespace {
	const QString COLUMNS = " id, text ";
	const QString TABLE_NAME = " scenario ";
}

Scenario* ScenarioMapper::find(const Identifier& _id)
{
	return dynamic_cast<Scenario*>(abstractFind(_id));
}

ScenariosTable* ScenarioMapper::findAll()
{
	return qobject_cast<ScenariosTable*>(abstractFindAll());
}

void ScenarioMapper::insert(Scenario* _scenario)
{
	abstractInsert(_scenario);
}

void ScenarioMapper::update(Scenario* _scenario)
{
	abstractUpdate(_scenario);
}

QString ScenarioMapper::findStatement(const Identifier& _id) const
{
	QString findStatement =
			QString("SELECT " + COLUMNS +
					" FROM " + TABLE_NAME +
					" WHERE id = %1 "
					)
			.arg(_id.value());
	return findStatement;
}

QString ScenarioMapper::findAllStatement() const
{
	return "SELECT " + COLUMNS + " FROM  " + TABLE_NAME;
}

QString ScenarioMapper::maxIdStatement() const
{
	return "SELECT MAX(id) FROM  " + TABLE_NAME;
}

QString ScenarioMapper::insertStatement(DomainObject* _subject, QVariantList& _insertValues) const
{
	QString insertStatement =
			QString("INSERT INTO " + TABLE_NAME +
					" (id, text) "
					" VALUES(?, ?) "
					);

	Scenario* scenario = dynamic_cast<Scenario*>(_subject );
	_insertValues.clear();
	_insertValues.append(scenario->id().value());
	_insertValues.append(scenario->text());

	return insertStatement;
}

QString ScenarioMapper::updateStatement(DomainObject* _subject, QVariantList& _updateValues) const
{
	QString updateStatement =
			QString("UPDATE " + TABLE_NAME +
					" SET text = ? "
					" WHERE id = ? "
					);

	Scenario* scenario = dynamic_cast<Scenario*>(_subject);
	_updateValues.clear();
	_updateValues.append(scenario->text());
	_updateValues.append(scenario->id().value());

	return updateStatement;
}

QString ScenarioMapper::deleteStatement(DomainObject* _subject, QVariantList& _deleteValues) const
{
	QString deleteStatement = "DELETE FROM " + TABLE_NAME + " WHERE id = ?";

	_deleteValues.clear();
	_deleteValues.append(_subject->id().value());

	return deleteStatement;
}

DomainObject* ScenarioMapper::doLoad(const Identifier& _id, const QSqlRecord& _record)
{
	QString text = _record.value("text").toString();

	return new Scenario(_id, text);
}

DomainObjectsItemModel* ScenarioMapper::modelInstance()
{
	return new ScenariosTable;
}

ScenarioMapper::ScenarioMapper()
{
}
