package net.sf.sevenzipjbinding.junit.compression;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.fail;

import java.util.Date;

import org.junit.Test;

import net.sf.sevenzipjbinding.ArchiveFormat;
import net.sf.sevenzipjbinding.IInArchive;
import net.sf.sevenzipjbinding.IOutCreateArchive;
import net.sf.sevenzipjbinding.IOutCreateCallback;
import net.sf.sevenzipjbinding.IOutItemAllFormats;
import net.sf.sevenzipjbinding.IOutUpdateArchive;
import net.sf.sevenzipjbinding.ISequentialInStream;
import net.sf.sevenzipjbinding.PropID;
import net.sf.sevenzipjbinding.SevenZip;
import net.sf.sevenzipjbinding.SevenZipException;
import net.sf.sevenzipjbinding.impl.OutItemFactory;
import net.sf.sevenzipjbinding.junit.JUnitNativeTestBase;
import net.sf.sevenzipjbinding.junit.VoidContext;
import net.sf.sevenzipjbinding.junit.tools.VirtualContent;
import net.sf.sevenzipjbinding.junit.tools.VirtualContent.VirtualContentConfiguration;
import net.sf.sevenzipjbinding.util.ByteArrayStream;

public class StandaloneUpdateArchiveUpdatePropertiesTest extends JUnitNativeTestBase<VoidContext>{
    private String newPath;
    private Date newModificationTime;
    private Integer newAttributes;
    private String newComment;

    /**
     * Tests updating archive item properties: PATH, LAST_MODIFICATION_TIME, ATTRIBUTES, COMMENT.
     * These are the main modifiable properties for 7z archives during update operations.
     */

    private class UpdateItemContentArchiveUpdateCallback implements IOutCreateCallback<IOutItemAllFormats> {
        private int itemToUpdate;

        public UpdateItemContentArchiveUpdateCallback(int itemToUpdate) {
            this.itemToUpdate = itemToUpdate;
        }

        public void setOperationResult(boolean operationResultOk) throws SevenZipException {
        }

        public void setTotal(long total) throws SevenZipException {
        }

        public void setCompleted(long complete) throws SevenZipException {

        }

        public IOutItemAllFormats getItemInformation(int index, OutItemFactory<IOutItemAllFormats> outItemFactory)
                throws SevenZipException {

            if (index == itemToUpdate) {
                IOutItemAllFormats outItem = outItemFactory.createOutItemAndCloneProperties(index);

                outItem.setUpdateIsNewProperties(Boolean.TRUE);

                // Update all testable properties
                outItem.setPropertyPath(newPath);
                outItem.setPropertyLastModificationTime(newModificationTime);
                outItem.setPropertyAttributes(newAttributes);
                outItem.setPropertyComment(newComment);

                return outItem;
            }

            return outItemFactory.createOutItem(index);
        }

        public ISequentialInStream getStream(int index) throws SevenZipException {
            return null;
        }
    }

    @Test
    public void updatePropreties() throws Exception {
        VirtualContent virtualContent = new VirtualContent(new VirtualContentConfiguration());
        virtualContent.fillRandomly(10, 1, 1, 100, 50, null, false);


        ByteArrayStream byteArrayStream = compressVirtualContext(virtualContent);
        byteArrayStream.rewind();

        ByteArrayStream byteArrayStream2 = new ByteArrayStream(100000);

        IInArchive inArchive = closeLater(SevenZip.openInArchive(ArchiveFormat.SEVEN_ZIP, byteArrayStream));
        int itemToUpdate = virtualContent.getItemCount() / 2;

        String itemToUpdatePath = (String) inArchive.getProperty(itemToUpdate, PropID.PATH);

        IOutUpdateArchive<IOutItemAllFormats> outArchiveConnected = inArchive.getConnectedOutArchive();

        newPath = inArchive.getProperty(itemToUpdate, PropID.PATH) + "_changed";
        newModificationTime = new Date(System.currentTimeMillis() + getRandom().nextInt(100000) + 100000);
        // Set attributes with standard file permission bits (readable, writable, executable by owner)
        newAttributes = Integer.valueOf(0x81A4); // Unix: -rwxr-xr-x (regular file with execute)
        newComment = "Test comment for item " + itemToUpdate;

        outArchiveConnected.updateItems(byteArrayStream2, inArchive.getNumberOfItems(),
                new UpdateItemContentArchiveUpdateCallback(itemToUpdate));

        byteArrayStream2.rewind();

        IInArchive modifiedInArchive = closeLater(SevenZip.openInArchive(null, byteArrayStream2));

        try {
            virtualContent.verifyInArchive(modifiedInArchive);
            fail("The content of the item with id " + itemToUpdate + " should differ");
        } catch (SevenZipException e) {
            AssertionError error = getExceptionCauseByClass(AssertionError.class, e);
            assertEquals("Directory passed to extraction (or index for path not found: '" + newPath + "')",
                    error.getMessage());
            // continue
        }

        virtualContent.updateItemLastModificationTimeByPath(itemToUpdatePath, newModificationTime);
        virtualContent.updateItemAttributesByPath(itemToUpdatePath, newAttributes);
        virtualContent.updateItemPathByPath(itemToUpdatePath, newPath);
        virtualContent.verifyInArchive(modifiedInArchive);
        
        // Verify the additional properties we set (COMMENT is not read-back supported in binding)
        verifyUpdatedProperties(modifiedInArchive, itemToUpdate, newPath, newAttributes);
    }

    private void verifyUpdatedProperties(IInArchive inArchive, int index, String expectedPath, 
            Integer expectedAttributes) throws SevenZipException {
        // Verify PATH (already done by virtualContent.verifyInArchive)
        
        // Verify ATTRIBUTES
        Integer actualAttributes = (Integer) inArchive.getProperty(index, PropID.ATTRIBUTES);
        assertNotNull("ATTRIBUTES should be set after update", actualAttributes);
        assertEquals("ATTRIBUTES mismatch after update", expectedAttributes.intValue(), actualAttributes.intValue());
        
        // Also verify via simple interface
        Integer simpleAttributes = inArchive.getSimpleInterface().getArchiveItem(index).getAttributes();
        
        assertEquals("Simple interface ATTRIBUTES mismatch", expectedAttributes.intValue(), simpleAttributes.intValue());
    }


    private ByteArrayStream compressVirtualContext(VirtualContent virtualContent) throws SevenZipException {
        ByteArrayStream byteArrayStream = new ByteArrayStream(100000);
        IOutCreateArchive<IOutItemAllFormats> outArchive = closeLater(SevenZip.openOutArchive(ArchiveFormat.SEVEN_ZIP));
        virtualContent.createOutArchive(outArchive, byteArrayStream);
        return byteArrayStream;
    }
}
