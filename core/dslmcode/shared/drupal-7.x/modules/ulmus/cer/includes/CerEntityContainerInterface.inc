<?php

/**
 * @interface
 *
 * This interface should be implemented by field plugins which can create embedded
 * entities on the fly.
 *
 * The prime example is field collections. CER might need to add a backreference on
 * a field which is in a field collection, yet there might be no field collection items
 * on which to add the reference. In that case, a new field collection item must be
 * be created and referenced properly by the owner.
 */
interface CerEntityContainerInterface {

  /**
   * Creates an embedded entity.
   *
   * @return EntityDrupalWrapper
   *  The newly created embedded entity, in a metadata wrapper.
   */
  public function createInnerEntity(EntityDrupalWrapper $owner);

}
