#ifndef CSM_PREFS_SHORTCUT_H
#define CSM_PREFS_SHORTCUT_H

#include <string>

#include <QKeySequence>
#include <QObject>
#include <QString>

class QKeyEvent;
class QMouseEvent;
class QShortcut;

namespace CSMPrefs
{
    /// A class similar in purpose to QShortcut, but with the ability to use mouse buttons
    class Shortcut : public QObject
    {
            Q_OBJECT

        public:

            enum ActivationStatus
            {
                AS_Regular,
                AS_Secondary,
                AS_Inactive
            };

            enum SecondaryMode
            {
                SM_Replace, ///< The secondary signal replaces the regular signal when the modifier is active
                SM_Detach,  ///< The secondary signal is emitted independant of the regular signal, even if not active
                SM_Ignore   ///< The secondary signal will not ever be emitted
            };

            Shortcut(const std::string& name, QObject* parent);
            Shortcut(const std::string& name, SecondaryMode secMode, QObject* parent);

            ~Shortcut();

            bool isEnabled() const;

            const std::string& getName() const;
            SecondaryMode getSecondaryMode() const;

            const QKeySequence& getSequence() const;
            int getModifier() const;

            /// The position in the sequence
            int getPosition() const;
            /// The position in the sequence
            int getLastPosition() const;

            ActivationStatus getActivationStatus() const;
            bool getModifierStatus() const;

            void enable(bool state);

            void setSequence(const QKeySequence& sequence);
            void setModifier(int modifier);

            /// The position in the sequence
            void setPosition(int pos);

            void setActivationStatus(ActivationStatus status);
            void setModifierStatus(bool status);

            QString toString() const;

        private:

            bool mEnabled;

            std::string mName;
            SecondaryMode mSecondaryMode;
            QKeySequence mSequence;
            int mModifier;

            int mCurrentPos;
            int mLastPos;

            ActivationStatus mActivationStatus;
            bool mModifierStatus;


        signals:

            /// Triggered when the shortcut is activated or deactivated; can be determined from \p state
            void activated(bool state);

            /// Convenience signal.
            void activated();

            /// Triggered depending on SecondaryMode
            void secondary(bool state);

            /// Convenience signal.
            void secondary();
    };
}

#endif
