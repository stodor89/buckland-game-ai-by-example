<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">
  <xsl:include href="reference.xsl"/>

  <xsl:output method="xml"
    doctype-public="-//OASIS//DTD DocBook XML V4.2//EN"
    doctype-system="http://www.oasis-open.org/docbook/xml/4.2/docbookx.dtd"/>

  <!-- The maximum number of columns allowed in preformatted text -->
  <xsl:param name="max-columns" select="78"/>

  <!-- The root of the Boost directory -->
  <xsl:param name="boost.root" select="'./'"/>

  <!-- A space-separated list of libraries to include in the
       output. If this list is empty, all libraries will be included. -->
  <xsl:param name="boost.include.libraries" select="''"/>

  <xsl:template match="library-reference">
    <xsl:choose>
      <xsl:when test="ancestor::library-reference">
        <xsl:apply-templates/>
      </xsl:when>
      <xsl:otherwise>
        <section>
          <xsl:choose>
            <xsl:when test="@id">
              <xsl:attribute name="id">
                <xsl:value-of select="@id"/>
              </xsl:attribute>
            </xsl:when>
            <xsl:when test="ancestor::library/attribute::id">
              <xsl:attribute name="id">
                <xsl:value-of select="ancestor::library/attribute::id"/>
                <xsl:text>.reference</xsl:text>
              </xsl:attribute>
            </xsl:when>
          </xsl:choose>
          <xsl:if test="not(title)">
            <title>
              <xsl:text>Reference</xsl:text>
            </title>    
          </xsl:if>

          <xsl:if test="concept">
            <section>
              <title>Concepts</title>

              <xsl:if test="ancestor::library/attribute::id">
                <xsl:attribute name="id">
                  <xsl:value-of select="ancestor::library/attribute::id"/>
                  <xsl:text>.concepts</xsl:text>
                </xsl:attribute>
              </xsl:if>

              <itemizedlist>
                <xsl:for-each select="concept">
                  <listitem>
                    <xsl:call-template name="internal-link">
                      <xsl:with-param name="to">
                        <xsl:call-template name="generate.id"/>
                      </xsl:with-param>
                      <xsl:with-param name="text" select="@name"/>
                    </xsl:call-template>
                  </listitem>
                </xsl:for-each>
              </itemizedlist>
            </section>
          </xsl:if>

          <xsl:apply-templates/>
        </section>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template match="header">
    <xsl:if test="*">
      <section>
        <xsl:attribute name="id">
          <xsl:call-template name="generate.id"/>
        </xsl:attribute>

        <title>
          <xsl:text>Header &lt;</xsl:text>
          <ulink>
            <xsl:attribute name="url">
              <xsl:text>../../</xsl:text>
              <xsl:value-of select="@name"/>
            </xsl:attribute>
            <xsl:value-of select="@name"/>
          </ulink>
          <xsl:text>&gt;</xsl:text>
        </title>

        <xsl:apply-templates select="para|section" mode="annotation"/>
        
        <xsl:if test="macro">
          <xsl:call-template name="synopsis">
            <xsl:with-param name="text">
              <xsl:apply-templates mode="synopsis" select="macro">
                <xsl:with-param name="indentation" select="0"/>
              </xsl:apply-templates>
            </xsl:with-param>
          </xsl:call-template>
        </xsl:if>

        <xsl:apply-templates mode="synopsis" select="namespace">
          <xsl:with-param name="indentation" select="0"/>
        </xsl:apply-templates>
        
        <xsl:apply-templates mode="reference"/>
      </section>
    </xsl:if>
  </xsl:template>

  <xsl:template match="header" mode="generate.id">
    <xsl:text>header.</xsl:text>
    <xsl:value-of select="translate(@name, '/','.')"/>
  </xsl:template>

  <xsl:template match="*" mode="passthrough">
    <xsl:copy-of select="."/>
  </xsl:template>

  <!-- Syntax highlighting -->
  <xsl:template name="highlight-keyword">
    <xsl:param name="keyword"/>
    <xsl:choose>
      <xsl:when test="$boost.syntax.highlight='1'">
        <emphasis role="bold"><xsl:value-of select="$keyword"/></emphasis>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="$keyword"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template name="highlight-comment">
    <xsl:param name="text"/>
    <emphasis><xsl:copy-of select="$text"/></emphasis>
  </xsl:template>

  <xsl:template name="monospaced">
    <xsl:param name="text"/>
    <computeroutput><xsl:value-of select="$text"/></computeroutput>
  </xsl:template>

  <!-- Linking -->
  <xsl:template name="internal-link">
    <xsl:param name="to"/>
    <xsl:param name="text"/>
    <xsl:param name="highlight" select="false()"/>

    <link linkend="{$to}">
      <xsl:if test="$highlight">
        <xsl:call-template name="source-highlight">
          <xsl:with-param name="text" select="$text"/>
        </xsl:call-template>
      </xsl:if>
      <xsl:if test="not($highlight)">
        <xsl:value-of select="string($text)"/>
      </xsl:if>
    </link>
  </xsl:template>

  <xsl:template name="anchor">
    <xsl:param name="to"/>
    <xsl:param name="text"/>
    <xsl:param name="highlight" select="false()"/>

    <anchor id="{$to}"/>
    <xsl:if test="$highlight">
      <xsl:call-template name="source-highlight">
        <xsl:with-param name="text" select="$text"/>
      </xsl:call-template>
    </xsl:if>
    <xsl:if test="not($highlight)">
      <xsl:value-of select="$text"/>
    </xsl:if>
  </xsl:template>

  <xsl:template name="link-or-anchor">
    <xsl:param name="to"/>
    <xsl:param name="text"/>

    <!-- True if we should create an anchor, otherwise we will create
         a link. If you require more control (e.g., with the possibility of
         having no link or anchor), set link-type instead: if present, it
         takes precedence. -->
    <xsl:param name="is-anchor"/>

    <!-- 'anchor', 'link', or 'none' -->
    <xsl:param name="link-type">
      <xsl:choose>
        <xsl:when test="$is-anchor">
          <xsl:text>anchor</xsl:text>
        </xsl:when>
        <xsl:otherwise>
          <xsl:text>link</xsl:text>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:param>

    <xsl:param name="highlight" select="false()"/>

    <xsl:choose>
      <xsl:when test="$link-type='anchor'">
        <xsl:call-template name="anchor">
          <xsl:with-param name="to" select="$to"/>
          <xsl:with-param name="text" select="$text"/>
          <xsl:with-param name="highlight" select="$highlight"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:when test="$link-type='link'">
        <xsl:call-template name="internal-link">
          <xsl:with-param name="to" select="$to"/>
          <xsl:with-param name="text" select="$text"/>
          <xsl:with-param name="highlight" select="$highlight"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:when test="$link-type='none'">
        <xsl:if test="$highlight">
          <xsl:call-template name="source-highlight">
            <xsl:with-param name="text" select="$text"/>
          </xsl:call-template>
        </xsl:if>
        <xsl:if test="not($highlight)">
          <xsl:value-of select="$text"/>
        </xsl:if>        
      </xsl:when>
      <xsl:otherwise>
        <xsl:message>
Error: XSL template 'link-or-anchor' called with invalid link-type '<xsl:value-of select="$link-type"/>'
        </xsl:message>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template name="separator"/>

  <xsl:template name="reference-documentation">
    <xsl:param name="name"/>
    <xsl:param name="refname"/>
    <xsl:param name="purpose"/>
    <xsl:param name="anchor"/>
    <xsl:param name="synopsis"/>
    <xsl:param name="text"/>

    <refentry id="{$anchor}">
      <refmeta>
        <refentrytitle><xsl:value-of select="$name"/></refentrytitle>
        <manvolnum>3</manvolnum>
      </refmeta>
      <refnamediv>
        <refname><xsl:value-of select="$refname"/></refname>
        <refpurpose><xsl:value-of select="$purpose"/></refpurpose>
      </refnamediv>
      <refsynopsisdiv>
        <synopsis>
          <xsl:copy-of select="$synopsis"/>
        </synopsis>
      </refsynopsisdiv>
      <xsl:if test="not(string($text)='')">
        <refsect1>
          <title>Description</title>
          <xsl:copy-of select="$text"/>
        </refsect1>
      </xsl:if>
    </refentry>
  </xsl:template>

  <xsl:template name="member-documentation">
    <xsl:param name="name"/>
    <xsl:param name="text"/>

    <refsect2>
      <title><xsl:copy-of select="$name"/></title>
      <xsl:copy-of select="$text"/>
    </refsect2>
  </xsl:template>

  <xsl:template name="preformatted">
    <xsl:param name="text"/>

    <literallayout class="monospaced">
      <xsl:copy-of select="$text"/>
    </literallayout>
  </xsl:template>

  <xsl:template name="synopsis">
    <xsl:param name="text"/>

    <synopsis>
      <xsl:copy-of select="$text"/>
    </synopsis>
  </xsl:template>

  <!-- Fallthrough for DocBook elements -->
  <xsl:template match="*">
    <xsl:element name="{name(.)}">
      <xsl:for-each select="./@*">
        <xsl:choose>
          <xsl:when test="local-name(.)='last-revision'">
            <xsl:attribute 
              name="rev:last-revision"
              namespace="http://www.cs.rpi.edu/~gregod/boost/tools/doc/revision">
              <xsl:value-of select="."/>
            </xsl:attribute>
          </xsl:when>
          <xsl:otherwise>
            <xsl:attribute name="{name(.)}">
              <xsl:value-of select="."/>
            </xsl:attribute>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:for-each>
      <xsl:apply-templates/>
    </xsl:element>
  </xsl:template>

  <xsl:template match="code">
    <computeroutput>
      <xsl:apply-templates mode="annotation"/>
    </computeroutput>
  </xsl:template>

  <xsl:template match="library">
    <xsl:if test="not(@html-only = 1) and
                  ($boost.include.libraries='' or
                   contains($boost.include.libraries, @id))">
      <chapter>
        <xsl:attribute name="id">
          <xsl:choose>
            <xsl:when test="@id">
              <xsl:value-of select="@id"/>
            </xsl:when>
            <xsl:otherwise>
              <xsl:call-template name="generate.id"/>
            </xsl:otherwise>
          </xsl:choose>
        </xsl:attribute>

        <xsl:if test="@last-revision">
          <xsl:attribute 
            name="rev:last-revision"
            namespace="http://www.cs.rpi.edu/~gregod/boost/tools/doc/revision">
            <xsl:value-of select="@last-revision"/>
          </xsl:attribute>
        </xsl:if>
        <xsl:apply-templates/>
      </chapter>
    </xsl:if>
  </xsl:template>

  <xsl:template match="chapter">
    <xsl:if test="$boost.include.libraries=''">
      <chapter>
        <xsl:for-each select="./@*">
          <xsl:attribute name="{name(.)}">
            <xsl:value-of select="."/>
          </xsl:attribute>
        </xsl:for-each>

        <xsl:apply-templates/>
      </chapter>
    </xsl:if>
  </xsl:template>

  <xsl:template match="boostbook">
    <book><xsl:apply-templates/></book>
  </xsl:template>

  <xsl:template match="programlisting">
    <programlisting><xsl:apply-templates/></programlisting>
  </xsl:template>

  <!-- These DocBook elements have special meaning. Use the annotation mode -->
  <xsl:template match="classname|methodname|functionname|libraryname|
                       conceptname|macroname|headername">
    <xsl:apply-templates select="." mode="annotation"/>
  </xsl:template>

  <xsl:template match="description">
    <xsl:apply-templates mode="annotation"/>
  </xsl:template>

  <!-- Swallow using-namespace and using-class directives along with
       last-revised elements -->
  <xsl:template match="using-namespace|using-class|last-revised"/>
</xsl:stylesheet>
