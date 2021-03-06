#ifndef _ShipDesignPanel_h_
#define _ShipDesignPanel_h_

#include <GG/GGFwd.h>
#include <GG/Control.h>


/** Represents a ShipDesign */
class ShipDesignPanel : public GG::Control {
public:
    /** \name Structors */ //@{
    ShipDesignPanel(GG::X w, GG::Y h, int design_id);   ///< basic ctor
    //@}

    /** \name Accessors */ //@{
    int                     DesignID() const {return m_design_id;}
    //@}

    /** \name Mutators */ //@{
    virtual void            SizeMove(const GG::Pt& ul, const GG::Pt& lr);
    virtual void            Render();

    void                    Update();
    //@}

private:
    int                     m_design_id;        ///< id for the ShipDesign this panel displays

protected:
    GG::StaticGraphic*      m_graphic;
    GG::Label*              m_name;
};

#endif
